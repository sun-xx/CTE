//By @Sun-XX
//�����㷨

#include <cmath> 

float get_distance(float x1,float y1,float x2,float y2){
	//����� �������� 
	return Qsqrt((x2 - y1)*(x2 - y1) - (y2 - y1)*(y2 - y1)); //����	
} 

float get_angle(float x1,float y1,float x2,float y2){
	//���� �������� 
	return (atan2((x2 - x1),(y2 - y1))*180/3.1415); //������ 
}


