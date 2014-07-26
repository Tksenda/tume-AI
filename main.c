#include<stdio.h>
#include<stdlib.h>

int ban[9][9],tume_tesuu,motigoma[64],motigoma_number,bit_ban[9][9];
int gyoku_x,gyoku_y,outegoma_x,outegoma_y;

int load(void);
int attack(void);
int defense(void);
int check_tume(void);
int kiki(void);
int gyoku_nige(void);
int outegoma(int y,int x,int y1,int x1);
int output(void);

int main(void){
	int i;
	i=1;
	load();
	kiki();
	int j,k;
	for(j=0;j<9;j++){
		for(k=0;k<9;k++){
			printf(" %d",bit_ban[j][k]);
		}
		printf("\n");
	}
	printf("%d %d\n",outegoma_y,outegoma_x);
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
		if(motigoma[i] == 0){
			motigoma_number=i;
			break;
		}
		i++;
	}
	return 0;
}

int attack(void){
	return 0;
}

int defense(void){
	return 0;
}

int check_tume(void){
	int i;
	kiki();
	if(bit_ban[gyoku_y][gyoku_x]==0){
		return -1;
	}
	i=gyoku_nige();
	if(i==-1){
		return -1;
	}
	return 0;
}

int kiki(void){
	int i,j,k;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(ban[i][j]>1000){
				bit_ban[i][j]=1;
			}else{
				switch(ban[i][j]){
					case 10:
						bit_ban[i-1][j]=1;
						outegoma(i-1,j,i,j);
						break;
					case 20:
						for(k=1;0<=i-k;k++){
							if(ban[i-k][j]==0){
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
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
							if(ban[i-k][j-k]==0){
								bit_ban[i-k][j-k]=1;
								outegoma(i-k,j-k,i,j);
							}else{
								bit_ban[i-k][j-k]=1;
								outegoma(i-k,j-k,i,j);
								break;
							}
						}
						for(k=1;i+k<=8 && 0<=j-k;k++){
							if(ban[i+k][j-k]==0){
								bit_ban[i+k][j-k]=1;
								outegoma(i+k,j-k,i,j);
							}else{
								bit_ban[i+k][j-k]=1;
								outegoma(i+k,j-k,i,j);
								break;
							}
						}
						for(k=1;i+k<=8 && j+k<=8;k++){
							if(ban[i+k][j+k]==0){
								bit_ban[i+k][j+k]=1;
								outegoma(i+k,j+k,i,j);
							}else{
								bit_ban[i+k][j+k]=1;
								outegoma(i+k,j+k,i,j);
								break;
							}
						}
						for(k=1;0<=i-k && j+k<=8;k++){
							if(ban[i-k][j+k]==0){
								bit_ban[i-k][j+k]=1;
								outegoma(i-k,j+k,i,j);
							}else{
								bit_ban[i-k][j+k]=1;
								outegoma(i-k,j+k,i,j);
								break;
							}
						}
						if(ban[i][j]==70){
							break;
						}else if(ban[i][j]==170){
							goto gyoku;
						}
					case 80:
					case 180:
						for(k=1;0<=j-k;k++){
							if(ban[i][j-k]==0){
								bit_ban[i][j-k]=1;
								outegoma(i,j-k,i,j);
							}else{
								bit_ban[i][j-k]=1;
								outegoma(i,j-k,i,j);
								break;
							}
						}
						for(k=1;j+k<=8;k++){
							if(ban[i][j+k]==0){
								bit_ban[i][j+k]=1;
								outegoma(i,j+k,i,j);
							}else{
								bit_ban[i][j+k]=1;
								outegoma(i,j+k,i,j);
								break;
							}
						}
						for(k=1;0<=i-k;k++){
							if(ban[i-k][j]==0){
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
							}else{
								bit_ban[i-k][j]=1;
								outegoma(i-k,j,i,j);
								break;
							}
						}
						for(k=1;i+k<=8;k++){
							if(ban[i+k][j]==0){
								bit_ban[i+k][j]=1;
								outegoma(i+k,j,i,j);
							}else{
								bit_ban[i+k][j]=1;
								outegoma(i+k,j,i,j);
								break;
							}
						}
						if(ban[i][j]==80){
							break;
						}else if(ban[i][j]==180){
							goto gyoku;
						}
					case 60:
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

int output(void){
	return 0;
}
