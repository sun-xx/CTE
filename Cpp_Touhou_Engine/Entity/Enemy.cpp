//By @Sun-XX

#include "Entity.hpp"

bool Enemy::hit_player(float player_tx,float player_ty,float player_x,float player_y,
						float player_r,float player_velocity){
	//��������&һԪ���η�������ӵ����Ի�һ֡�ڹ켣�Ƿ�����
	//����˳��Ϊ ��һ֡�Ի����꣬��֡�Ի����꣬�Ի��ж��뾶 
	if(get_distance(player_x,player_y,this->x,this->y) >
		(this->velocity + player_velocity + this->r + player_r)){
		//ɸ�����볬���ٶȡ��뾶֮�� ��������ײ 
		return false;
	}
	else{
		float X1,X2,Y1,Y2;
		X1 = temp_x - player_tx; X2 = this->x - player_x - X1;
		Y1 = temp_y - player_ty; Y2 = this->y - player_y - Y1;
		float a = X2*X2 + Y2*Y2,
		b = 2*(X1*X2 + Y1*Y2),
		c = X1*X1 + Y1*Y1 - r*r - player_r*player_r;
		float delta = b*b - 4*a*c;
		
		float t1 = (-b + Qsqrt(delta))/(2*a),
		t2 = (-b - Qsqrt(delta))/(2*a);
		
		return delta<0?false:((t1>=0 && t1<=1)||(t2>=0 && t1<=1)); //����һ�����̸��ڷ�Χ�ڼ��ж�����
	}
}

bool Bullet::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//�����ж�
	return !(this->x>screen_xl && this->x<screen_xr && this->y>screen_yb && this->y<screen_yt);
	//��������true ��֮����false
}
