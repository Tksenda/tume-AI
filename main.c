#include<stdio.h>
#include<stdlib.h>

int ban[9][9],tume_tesuu,motigoma[64],motigoma_number,bit_ban[9][9];
int gyoku_x,gyoku_y,outegoma_x,outegoma_y,bit_ban_enemy[9][9],tesuu;
int attack_level[256],defense_level[256],attack_level1_i[256][16];
int ban_think[9][9],kihu[512],motigoma_think[64];

int load(void);
int attack(void);
int attack_level1(void);
int defense(void);
int check_tume(void);
int kiki(void);
int gyoku_nige(void);
int outegoma(int y,int x,int y1,int x1);
int kiki_enemy(void);
int motigoma_seiri(int koma);
int back_ban(int back_tesuu);
int output(void);

int main(void){
	int i,j,k;
	load();
	for(;;){
		attack();
		tesuu++;
		i=check_tume();
		if(i==0){
			break;
		}else{
			back_ban(1);
		}
	}
	printf("詰ませました。\n");
	printf("最終図\n");
	for(j=0;j<9;j++){
			for(k=0;k<9;k++){
			printf(" %d",ban_think[j][k]);
		}
		printf("\n");
	}
	printf("棋譜(独自規格)\n");
	printf("%d\n",kihu[0]);
/*	for(;;){
		if(i%2 == 1){
			attack();
		}else{
			defense();
		}
	}*/
	return 0;
}

int load(void){
	int i,j;
	printf("詰め手数\n");
	scanf("%d",&tume_tesuu);
	printf("盤の情報\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			scanf("%d",&ban[i][j]);
			ban_think[i][j]=ban[i][j];
			if(ban[i][j]==1060){
				gyoku_x=j;
				gyoku_y=i;
			}
		}
	}
	printf("持ち駒情報\n");
	i=0;
	for(;;){
		scanf("%d",&motigoma[i]);
		motigoma_think[i]=motigoma[i];
		if(motigoma[i] == 0){
			motigoma_number=i;
			break;
		}
		i++;
	}
	return 0;
}

int attack(void){
	switch(attack_level[tesuu/2+tesuu%2]){
		case 0:
			attack_level1();
			break;
	}
	return 0;
}

int attack_level1(void){
	switch(motigoma_think[attack_level1_i[tesuu/2+tesuu%2][0]]){
		case 0:
			attack_level[tesuu]++;
			break;
		case 10:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(ban_think[gyoku_y+1][gyoku_x]==0){
						ban_think[gyoku_y+1][gyoku_x]=10;
						motigoma_seiri(10);
						kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y+1))*1000+10;
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
		case 20:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(ban_think[gyoku_y+1][gyoku_x]==0){
						ban_think[gyoku_y+1][gyoku_x]=20;
						motigoma_seiri(20);
						kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y+1))*1000+20;
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
		case 30:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(0<=gyoku_x-1 && gyoku_y+2<=8){
						if(ban_think[gyoku_y+2][gyoku_x-1]==0){
							ban_think[gyoku_y+2][gyoku_x-1]=30;
							motigoma_seiri(30);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+(gyoku_y+2))*1000+30;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					if(gyoku_x+1<=8 && gyoku_y+2<=8){
						if(ban_think[gyoku_y+2][gyoku_x+1]==0){
							ban_think[gyoku_y+2][gyoku_x+1]=30;
							motigoma_seiri(30);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+(gyoku_y+2))*1000+30;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 2:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
		case 40:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(0<=gyoku_x-1 && gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x-1]==0){
							ban_think[gyoku_y+1][gyoku_x-1]=40;
							motigoma_seiri(40);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+(gyoku_y+1))*1000+40;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					if(gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x]==0){
							ban_think[gyoku_y+1][gyoku_x]=40;
							motigoma_seiri(40);
							kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y+1))*1000+40;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 2:
					if(gyoku_x+1<=8 && gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x+1]==0){
							ban_think[gyoku_y+1][gyoku_x+1]=40;
							motigoma_seiri(40);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+(gyoku_y+1))*1000+40;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 3:
					if(gyoku_x+1<=8 && 0<=gyoku_y-1){
						if(ban_think[gyoku_y-1][gyoku_x+1]==0){
							ban_think[gyoku_y-1][gyoku_x+1]=40;
							motigoma_seiri(40);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+(gyoku_y-1))*1000+40;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 4:
					if(0<=gyoku_x-1 && 0<=gyoku_y-1){
						if(ban_think[gyoku_y-1][gyoku_x-1]==0){
							ban_think[gyoku_y-1][gyoku_x-1]=40;
							motigoma_seiri(40);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+(gyoku_y-1))*1000+40;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 5:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
		case 50:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(0<=gyoku_x-1 && gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x-1]==0){
							ban_think[gyoku_y+1][gyoku_x-1]=50;
							motigoma_seiri(50);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+(gyoku_y+1))*1000+50;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					if(gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x]==0){
							ban_think[gyoku_y+1][gyoku_x]=50;
							motigoma_seiri(50);
							kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y+1))*1000+50;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 2:
					if(gyoku_x+1<=8 && gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x+1]==0){
							ban_think[gyoku_y+1][gyoku_x+1]=50;
							motigoma_seiri(50);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+(gyoku_y+1))*1000+50;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 3:
					if(gyoku_x+1<=8){
						if(ban_think[gyoku_y][gyoku_x+1]==0){
							ban_think[gyoku_y][gyoku_x+1]=50;
							motigoma_seiri(50);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+gyoku_y)*1000+50;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 4:
					if(0<=gyoku_y-1){
						if(ban_think[gyoku_y-1][gyoku_x]==0){
							ban_think[gyoku_y-1][gyoku_x]=50;
							motigoma_seiri(50);
							kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y-1))*1000+50;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 5:
					if(0<=gyoku_x-1){
						if(ban_think[gyoku_y][gyoku_x-1]==0){
							ban_think[gyoku_y][gyoku_x-1]=50;
							motigoma_seiri(50);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+gyoku_y)*1000+50;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 6:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
		case 70:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x]==0){
							ban_think[gyoku_y+1][gyoku_x]=70;
							motigoma_seiri(70);
							kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y+1))*1000+70;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					if(gyoku_x+1<=8){
						if(ban_think[gyoku_y][gyoku_x+1]==0){
							ban_think[gyoku_y][gyoku_x+1]=70;
							motigoma_seiri(70);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+gyoku_y)*1000+70;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 2:
					if(0<=gyoku_y-1){
						if(ban_think[gyoku_y-1][gyoku_x]==0){
							ban_think[gyoku_y-1][gyoku_x]=70;
							motigoma_seiri(70);
							kihu[tesuu]=(99*100+gyoku_x*10+(gyoku_y-1))*1000+70;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 3:
					if(0<=gyoku_x-1){
						if(ban_think[gyoku_y][gyoku_x-1]==0){
							ban_think[gyoku_y][gyoku_x-1]=70;
							motigoma_seiri(70);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+gyoku_y)*1000+70;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 4:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
		case 80:
			switch(attack_level1_i[tesuu/2+tesuu%2][1]){
				case 0:
					if(0<=gyoku_x-1 && gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x-1]==0){
							ban_think[gyoku_y+1][gyoku_x-1]=80;
							motigoma_seiri(80);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+(gyoku_y+1))*1000+80;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 1:
					if(gyoku_x+1<=8 && gyoku_y+1<=8){
						if(ban_think[gyoku_y+1][gyoku_x+1]==0){
							ban_think[gyoku_y+1][gyoku_x+1]=80;
							motigoma_seiri(80);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+(gyoku_y+1))*1000+80;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 2:
					if(gyoku_x+1<=8 && 0<=gyoku_y-1){
						if(ban_think[gyoku_y-1][gyoku_x+1]==0){
							ban_think[gyoku_y-1][gyoku_x+1]=80;
							motigoma_seiri(80);
							kihu[tesuu]=(99*100+(gyoku_x+1)*10+(gyoku_y-1))*1000+80;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 3:
					if(0<=gyoku_x-1 && 0<=gyoku_y-1){
						if(ban_think[gyoku_y-1][gyoku_x-1]==0){
							ban_think[gyoku_y-1][gyoku_x-1]=80;
							motigoma_seiri(80);
							kihu[tesuu]=(99*100+(gyoku_x-1)*10+(gyoku_y-1))*1000+80;
						}
					}
					attack_level1_i[tesuu/2+tesuu%2][1]++;
					break;
				case 4:
					attack_level1_i[tesuu/2+tesuu%2][1]=0;
					attack_level1_i[tesuu/2+tesuu%2][0]++;
					break;
			}
			break;
	}
	return 0;
}

int defense(void){
	return 0;
}

int check_tume(void){
	int i,x,y;
	kiki();
	kiki_enemy();
	if(bit_ban[gyoku_y][gyoku_x]==0){
		printf("1\n");
		return -1;
	}
	i=gyoku_nige();
	if(i==-1){
		printf("2\n");
		return -1;
	}
	y=abs(outegoma_y-gyoku_y);
	x=abs(outegoma_x-gyoku_x);
	if(x<=1 && y<=1){
		if(bit_ban[outegoma_y][outegoma_x]==0){
			printf("3\n");
			return -1;
		}
	}
	if(bit_ban_enemy[outegoma_y][outegoma_x]==1){
		printf("4\n");
		return -1;
	}
	if(ban_think[outegoma_y][outegoma_x]!=30){
		if(2<=x || 2<=y){
			if(motigoma_number!=0){
				printf("5\n");
				return -1;
			}
		}
	}
	return 0;
}

int kiki(void){
	int i,j,k;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(ban_think[i][j]>1000){
				bit_ban[i][j]=1;
			}else{
				switch(ban_think[i][j]){
					case 10:
						bit_ban[i-1][j]=1;
						outegoma(i-1,j,i,j);
						break;
					case 20:
						for(k=1;0<=i-k;k++){
							if(ban_think[i-k][j]==0){
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
							}else if(ban_think[i-k][j]==1060){
								bit_ban[i-k][j]==1;
							}else{
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
								break;
							}
						}
						break;
					case 30:
						if(j<1){
							bit_ban[i-2][j+1]=1;
							outegoma(i-2,j+1,i,j);
							break;
						}
						if(7<j){
							bit_ban[i-2][j-1]=1;
							outegoma(i-2,j-1,i,j);
							break;
						}
						bit_ban[i-2][j-1]=1;
						outegoma(i-2,j-1,i,j);
						bit_ban[i-2][j+1]=1;
						outegoma(i-2,j+1,i,j);
						break;
					case 40:
						if(0<=i-1){
							if(0<=j-1){
								bit_ban[i-1][j-1]=1;
								outegoma(i-1,j-1,i,j);
							}
							bit_ban[i-1][j]=1;
							if(j+1<=8){
								bit_ban[i-1][j+1]=1;
								outegoma(i-1,j+1,i,j);
							}
						}
						if(i+1<=8){
							if(0<=j-1){
								bit_ban[i+1][j-1]=1;
								outegoma(i+1,j-1,i,j);
							}
							if(j+1<=8){
								bit_ban[i+1][j+1]=1;
								outegoma(i+1,j+1,i,j);
							}
						}
						break;
					case 50:
					case 110:
					case 120:
					case 130:
					case 140:
						if(0<=i-1){
							if(0<=j-1){
								bit_ban[i-1][j-1]=1;
								outegoma(i-1,j-1,i,j);
							}
							bit_ban[i-1][j]=1;
							outegoma(i-1,j,i,j);
							if(j+1<=8){
								bit_ban[i-1][j+1]=1;
								outegoma(i-1,j+1,i,j);
							}
						}
						if(0<=j-1){
							bit_ban[i][j-1]=1;
							outegoma(i,i-1,i,j);
						}
						if(j+1<=8){
							bit_ban[i][j+1]=1;
							outegoma(i,j+1,i,j);
						}
						if(i+1<=8){
							bit_ban[i+1][j]=1;
							outegoma(i+1,j,i,j);
						}
						break;
					case 70:
					case 170:
						for(k=1;0<=j-k && 0<=i-k;k++){
							if(ban_think[i-k][j-k]==0){
								bit_ban[i-k][j-k]=1;
								outegoma(i-k,j-k,i,j);
							}else if(ban_think[i-k][j-k]==1060){
								bit_ban[i-k][j-k]=1;
							}else{
								bit_ban[i-k][j-k]=1;
								outegoma(i-k,j-k,i,j);
								break;
							}
						}
						for(k=1;i+k<=8 && 0<=j-k;k++){
							if(ban_think[i+k][j-k]==0){
								bit_ban[i+k][j-k]=1;
								outegoma(i+k,j-k,i,j);
							}else if(ban_think[i+k][j-k]==1060){
								bit_ban[i+k][j-k]=1;
							}else{
								bit_ban[i+k][j-k]=1;
								outegoma(i+k,j-k,i,j);
								break;
							}
						}
						for(k=1;i+k<=8 && j+k<=8;k++){
							if(ban_think[i+k][j+k]==0){
								bit_ban[i+k][j+k]=1;
								outegoma(i+k,j+k,i,j);
							}else if(ban_think[i+k][j+k]==1060){
								bit_ban[i+k][j+k]=1;
							}else{
								bit_ban[i+k][j+k]=1;
								outegoma(i+k,j+k,i,j);
								break;
							}
						}
						for(k=1;0<=i-k && j+k<=8;k++){
							if(ban_think[i-k][j+k]==0){
								bit_ban[i-k][j+k]=1;
								outegoma(i-k,j+k,i,j);
							}else if(ban_think[i-k][j+k]==1060){
								bit_ban[i-k][j+k]=1;
							}else{
								bit_ban[i-k][j+k]=1;
								outegoma(i-k,j+k,i,j);
								break;
							}
						}
						if(ban_think[i][j]==70){
							break;
						}else if(ban_think[i][j]==170){
							goto gyoku;
						}
					case 80:
					case 180:
						for(k=1;0<=j-k;k++){
							if(ban_think[i][j-k]==0){
								bit_ban[i][j-k]=1;
								outegoma(i,j-k,i,j);
							}else if(ban_think[i][j-k]==1060){
								bit_ban[i][j-k]=1;
							}else{
								bit_ban[i][j-k]=1;
								outegoma(i,j-k,i,j);
								break;
							}
						}
						for(k=1;j+k<=8;k++){
							if(ban_think[i][j+k]==0){
								bit_ban[i][j+k]=1;
								outegoma(i,j+k,i,j);
							}else if(ban_think[i][j+k]==1060){
								bit_ban[i][j+k]=1;
							}else{
								bit_ban[i][j+k]=1;
								outegoma(i,j+k,i,j);
								break;
							}
						}
						for(k=1;0<=i-k;k++){
							if(ban_think[i-k][j]==0){
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
							}else if(ban_think[i-k][j]==1060){
								bit_ban[i-k][j]=1;
							}else{
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
								break;
							}
						}
						for(k=1;i+k<=8;k++){
							if(ban_think[i+k][j]==0){
								bit_ban[i+k][j]=1;
								outegoma(i+k,j,i,j);
							}else if(ban_think[i+k][j]==1060){
								bit_ban[i+k][j]=1;
							}else{
								bit_ban[i+k][j]=1;
								outegoma(i+k,j,i,j);
								break;
							}
						}
						if(ban_think[i][j]==80){
							break;
						}else if(ban_think[i][j]==180){
							goto gyoku;
						}
					case 60:
						break;
						gyoku:
						if(0<=i-1){
							if(0<=j-1){
								bit_ban[i-1][j-1]=1;
								outegoma(i-1,j-1,i,j);
							}
							bit_ban[i-1][j]=1;
							outegoma(i-1,j,i,j);
							if(j+1<=8){
								bit_ban[i-1][j+1]=1;
								outegoma(i-1,j+1,i,j);
							}
						}
						if(0<=j-1){
							bit_ban[i][j-1]=1;
							outegoma(i,j-1,i,j);
						}
						if(j+1<=8){
							bit_ban[i][j+1]=1;
							outegoma(i,j+1,i,j);
						}
						if(i+1<=8){
							if(0<=j-1){
								bit_ban[i+1][j-1]=1;
								outegoma(i+1,j-1,i,j);
							}
							bit_ban[i+1][j]=1;
							outegoma(i+1,j,i,j);
							if(j+1<=8){
								bit_ban[i+1][j+1]=1;
								outegoma(i+1,j+1,i,j);
							}
						}
						break;
				}
			}
		}
	}
	return 0;
}

int gyoku_nige(void){
	int i,j;
	i=gyoku_y;
	j=gyoku_x;
	if(0<=i-1){
		if(0<=j-1){
			if(bit_ban[i-1][j-1]==0){
				return -1;
			}
		}
		if(bit_ban[i-1][j]==0){
				return -1;
		}
		if(j+1<=8){
			if(bit_ban[i-1][j+1]==0){
				return -1;
			}
		}
	}
	if(0<=j-1){
		if(bit_ban[i][j-1]==0){
			return -1;
		}
	}
	if(j+1<=8){
		if(bit_ban[i][j+1]==0){
			return -1;
		}
	}
	if(i+1<=8){
		if(0<=j-1){
			if(bit_ban[i+1][j-1]==0){
				return -1;
			}
		}
		if(bit_ban[i+1][j]==0){
				return -1;
		}
		if(j+1<=8){
			if(bit_ban[i+1][j+1]==0){
				return -1;
			}
		}
	}
	return 0;
}

int outegoma(int y,int x,int y1,int x1){
	if(gyoku_x==x && gyoku_y==y){
		outegoma_x=x1;
		outegoma_y=y1;
	}
	return 0;
}

int kiki_enemy(void){
	int i,j,k;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			switch(ban_think[i][j]-1000){
				case 10:
					bit_ban_enemy[i+1][j]=1;
					break;
				case 20:
					for(k=1;i+k<=8;k++){
						if(ban_think[i+k][j]==0){
							bit_ban_enemy[i+k][j]=1;
						}else{
							bit_ban_enemy[i+k][j]=1;
							break;
						}
					}
					break;
				case 30:
					if(8<j+1){
						bit_ban_enemy[i+2][j-1]=1;
						break;
					}
					if(j-1<0){
						bit_ban_enemy[i+2][j+1]=1;
						break;
					}
					bit_ban_enemy[i+2][j-1]=1;
					bit_ban_enemy[i+2][j+1]=1;
					break;
				case 40:
					if(i+1<=8){
						if(j+1<=8){
							bit_ban_enemy[i+1][j+1]=1;
						}
						bit_ban_enemy[i+1][j]=1;
						if(0<=j-1){
							bit_ban_enemy[i+1][j-1]=1;
						}
					}
					if(0<=i-1){
						if(0<=j-1){
							bit_ban_enemy[i-1][j-1]=1;
						}
						if(j+1<=8){
							bit_ban_enemy[i-1][j+1]=1;
						}
					}
					break;
				case 50:
				case 110:
				case 120:
				case 130:
				case 140:
					if(i+1<=8){
						if(0<=j-1){
							bit_ban_enemy[i+1][j-1]=1;
						}
						bit_ban_enemy[i+1][j]=1;
						if(j+1<=8){
							bit_ban_enemy[i+1][j+1]=1;
						}
					}
					if(0<=j-1){
						bit_ban_enemy[i][j-1]=1;
					}
					if(j+1<=8){
						bit_ban_enemy[i][j+1]=1;
					}
					if(0<=i-1){
						bit_ban_enemy[i-1][j]=1;
					}
					break;
				case 70:
				case 170:
					for(k=1;0<=j-k && 0<=i-k;k++){
						if(ban_think[i-k][j-k]==0){
							bit_ban_enemy[i-k][j-k]=1;
						}else{
							bit_ban_enemy[i-k][j-k]=1;
							break;
						}
					}
					for(k=1;i+k<=8 && 0<=j-k;k++){
						if(ban_think[i+k][j-k]==0){
							bit_ban_enemy[i+k][j-k]=1;
						}else{
							bit_ban_enemy[i+k][j-k]=1;
							break;
						}
					}
					for(k=1;i+k<=8 && j+k<=8;k++){
						if(ban_think[i+k][j+k]==0){
							bit_ban_enemy[i+k][j+k]=1;
						}else{
							bit_ban_enemy[i+k][j+k]=1;
							break;
						}
					}
					for(k=1;0<=i-k && j+k<=8;k++){
						if(ban_think[i-k][j+k]==0){
							bit_ban_enemy[i-k][j+k]=1;
						}else{
							bit_ban_enemy[i-k][j+k]=1;
							break;
						}
					}
					if(ban_think[i][j]==1070){
						break;
					}else if(ban_think[i][j]==1170){
						goto gyoku;
					}
				case 80:
				case 180:
					for(k=1;0<=j-k;k++){
						if(ban_think[i][j-k]==0){
							bit_ban_enemy[i][j-k]=1;
						}else{
							bit_ban_enemy[i][j-k]=1;
							break;
						}
					}
					for(k=1;j+k<=8;k++){
						if(ban_think[i][j+k]==0){
							bit_ban_enemy[i][j+k]=1;
						}else{
							bit_ban_enemy[i][j+k]=1;
							break;
						}
					}
					for(k=1;0<=i-k;k++){
						if(ban_think[i-k][j]==0){
							bit_ban_enemy[i-k][j]=1;
						}else{
							bit_ban_enemy[i-k][j]=1;
							break;
						}
					}
					for(k=1;i+k<=8;k++){
						if(ban_think[i+k][j]==0){
							bit_ban_enemy[i+k][j]=1;
						}else{
							bit_ban_enemy[i+k][j]=1;
							break;
						}
					}
					if(ban_think[i][j]==1080){
						break;
					}else if(ban_think[i][j]==1180){
						goto gyoku;
					}
				case 60:
					break;
					gyoku:
					if(0<=i-1){
						if(0<=j-1){
							bit_ban_enemy[i-1][j-1]=1;
						}
						bit_ban_enemy[i-1][j]=1;
						if(j+1<=8){
							bit_ban_enemy[i-1][j+1]=1;
						}
					}
					if(0<=j-1){
						bit_ban_enemy[i][j-1]=1;
					}
					if(j+1<=8){
						bit_ban_enemy[i][j+1]=1;
					}
					if(i+1<=8){
						if(0<=j-1){
							bit_ban_enemy[i+1][j-1]=1;
						}
						bit_ban_enemy[i+1][j]=1;
						if(j+1<=8){
							bit_ban_enemy[i+1][j+1]=1;
						}
					}
					break;
			}
		}
	}
	return 0;
}

int motigoma_seiri(int koma){
	int i;
	for(i=0;i<motigoma_number;i++){
		if(motigoma_think[i]==koma){
			motigoma_think[i]=0;
			for(;i<motigoma_number;i++){
				motigoma_think[i]=motigoma_think[i+1];
			}
			break;
		}
	}
	return 0;
}

int back_ban(int back_tesuu){
	int i,j,k,l,x,y;
	for(j=0;j<8;j++){
		for(k=0;k<8;k++){
			ban_think[j][k]=ban[j][k];
		}
	}
	for(i=0;i<motigoma_number;i++){
		motigoma_think[i]=motigoma[i];
	}
	for(i=0;i<tesuu-back_tesuu;i++){
		if(9900000<=kihu[i]){
			motigoma_seiri(kihu[i]%1000);
			x=(kihu[i]-9900000)/10000;
			y=(kihu[i]-9900000)%10000;
			ban_think[y][x]=kihu[i]%1000;
		}
		if(kihu[i]<=-9900000){
		}
	}
	tesuu=tesuu-back_tesuu;
	return 0;
}

int output(void){
	return 0;
}
