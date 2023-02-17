#include "stdafx.h"
#include "vision_sensor.h"


vision_sensor::vision_sensor()
    :m_height(0),
    m_width(0)
{
}

int vision_sensor::width()
{
    return m_width;
}

int vision_sensor::height()
{
    return m_height;
}

void vision_sensor::start()
{
    int height, width; 
    HWND hwnd = GetDesktopWindow(); 
    RECT windowsize;
    GetClientRect(hwnd, &windowsize);
    height = windowsize.bottom / 1;
    width = windowsize.right / 1;
    m_height = height;
    m_width = width;

    m_src.create(m_height, m_width, CV_8UC4);

    m_vision_thread_break = false;
    m_vision_thread = g2thread(&vision_sensor::vision_thread, this);
}
void vision_sensor::stop()
{
    m_vision_thread_break = true;
    m_vision_thread.join();
}

g2vision_chanel* vision_sensor::data_start()
{
    return const_cast<g2vision_chanel*>(m_src.datastart);
}

g2vision_chanel* vision_sensor::data_end()
{
    return const_cast<g2vision_chanel*>(m_src.dataend);
}
 
void vision_sensor::vision_thread()
{
    while (m_vision_thread_break == false)
    {
        build_field();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void vision_sensor::lock()
{
    m_read_sensor_mutex.lock();
}

void vision_sensor::unlock()
{
    m_read_sensor_mutex.unlock();
}

void vision_sensor::build_field()
{
    m_read_sensor_mutex.lock();
    HDC hwindowDC, hwindowCompatibleDC;
    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    BITMAPINFOHEADER  bi;
    HWND hwnd = GetDesktopWindow();
    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);
    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom / 1;  //change this to whatever size you want to resize to
    width = windowsize.right / 1;
    m_height = height;
    m_width = width;
    // create a bitmap
    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, m_src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);
    m_read_sensor_mutex.unlock();
}

 