#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#pragma comment(lib,"opencv_world470d.lib")
using namespace cv;

class vision_sensor
{
public:
	vision_sensor();
	~vision_sensor();
	int width();
	int height();
	void start();
	void stop();
	g2vision_chanel* data_start();
	g2vision_chanel* data_end();
	void lock();
	void unlock();
protected:
	void build_field();
	void vision_thread();
private:
	Mat m_src;
	g2thread m_vision_thread;
	g2mutex m_read_sensor_mutex;
	g2int m_width;
	g2int m_height;
	volatile bool m_vision_thread_break;
};

