//By @Sun-XX
//常用算法

#include <cmath> 

float get_distance(float x1,float y1,float x2,float y2){
	//求距离 两组坐标 
	return Qsqrt((x2 - y1)*(x2 - y1) - (y2 - y1)*(y2 - y1)); //勾股	
} 

float get_angle(float x1,float y1,float x2,float y2){
	//求方向 两组坐标 
	return (atan2((x2 - x1),(y2 - y1))*180/3.1415); //反三角 
}


