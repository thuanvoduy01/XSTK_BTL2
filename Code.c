#include<stdio.h>

struct node { 
    int color; 
    float pro; 
    int arr[100]; 
    int top; 
} p[256]; 
	float size,H;

void Fano_Function(int l, int h,node p[]){
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0; 
	int i,j;									
	if((l+1)==h || l>=h){
		if(l>=h){
			return;
		}
		p[l].arr[++(p[l].top)]=0;
		p[h].arr[++(p[h].top)]=1;
		return;
	} 
	else{
		pack1=p[l].pro;
		for(i=l+1;i<=h;i++){
			pack2+=p[i].pro;
		}
		diff1= pack1 -pack2;
		if (diff1<0) {diff1=-diff1;}		
		
		j=l+1;
		while(j<=h-1){
			pack1 = pack2 = 0; 
			for (i=l;i<=j;i++){
				pack1+=p[i].pro;
			}
			for (i=j+1;i<=h;i++){
				pack2+=p[i].pro;
			}
			diff2=pack1- pack2;
			if(diff2<0){diff2=-diff2;}
			
			if(diff2>=diff1){
				break;
			}
			diff1=diff2;
			j++;
		}
		
		for (int a=l;a<=j-1;a++){
			p[a].arr[++(p[a].top)]=0;
		}
		for (int a=j;a<=h;a++){
			p[a].arr[++(p[a].top)]=1;
		}	
		Fano_Function(l,j-1,p);
		Fano_Function(j,h,p);
	}
}

void DecreasebyProbability(int n, node p[]){
	int i,j;
	node temp;
	for (i=0;i<=n-2;i++){
		for(j=i+1;j<=n-1;j++){
			if(p[j].pro>=p[i].pro){		
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}

void display_binary(int n,node p[]){
	int i,j;
	printf("\n\t\tColor\tProbability\tBit-Length\tBinary");
	for (i=0;i<=n-1;i++){
		if(p[i].pro>0){	
			printf("\n\t\t %d \t %f \t   %d \t\t",p[i].color,p[i].pro,p[i].top+1);
			for (j=0;j<=p[i].top;j++){
				printf("%d",p[i].arr[j]);
			}
		}
	}
}

void Func_after_compression(int n, node p[]){
	int length[n-1];
	for(int i=0;i<=n-1;i++){
		length[i]=p[i].top+1;
	}
	
	for(int i=0;i<=n-1;i++){
		size+=p[i].pro*length[i]*32*32;
	}
													
	H=size/(32*32*8);
																			
	printf("\n\n\tHieu suat ma hoa = (%.2f/%d)*100% = %f%c",size,32*32*8,H*100,'%');
}

int main(){
	int n, i, j; 
    float tong = 0; 
  	
  	printf("Nhap so mau:");
  	scanf("%d",&n);
  	
  	printf("Input the intensity of grayscale\n");
  	for (int i=0;i<=n-1;i++){
  		scanf("%d",&p[i].color);
	  }
  	
  	for(int i=0;i<=n-1;i++){
		printf("Tan suat cua mau %d la: ",p[i].color);
		scanf("%f",&p[i].pro);
		tong+=p[i].pro;
		if(tong>1){
			tong-=p[i].pro;
			printf("nhap gia tri sai\tTong xac xuat = %f\n",tong);
			i--;
		}
	}
	for (i = 0; i < n; i++) 
		p[i].top = -1;
	
	DecreasebyProbability(n,p);
	Fano_Function(0,n-1,p);
	display_binary(n,p);
	Func_after_compression(n,p);
	return 0;
}
