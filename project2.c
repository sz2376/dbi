#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void output(int p){
  int m, n;
	int array1 [13] = {0};
	for (m = 1; ; m ++) {
		array1 [m] = p % 2;
		p /= 2;
		if (p == 0) break;
	}
	for (n = 1; n <=m; n ++){
		if (array1[n] == 1) {printf("(t%d[o%d[i]]", n, n); break;}
	}
	for (n = n + 1; n <=m; n ++){
		if (array1[n] == 1) {printf(" & t%d[o%d[i]]", n, n);}
	}
	printf(")");
}

float code(float *arr,int *arr2){
  int count = 1;
  int max = 0;
  int flag = 0;
  int a = 0;
  int c = 0;
  int g = 0;
  int h = 0;
  int i = 0;
  int j = 0;
  int k = 1;
  int l = 0;
  int ll= 0; 
  int m = 0;
  int n = 0;
  int p = 0;
  int lll[50] = {0};
  int rr[50] = {0};
  int r[13] = {0};
  int s[13] = {0};
  int t[13] = {0};
  int y = 0;
  float fcost1=0;
  float fcost2=0;
  float q = 1;
  float qq = 0;
  float p1 = 1;
  float p2 = 1;
  float b = 0;

  // i counts the number of basic terms 
  while(arr[i] <= 1) {
    i++; // i is the total number of basic terms 
  }

  // k is total possible combinations 
  while (j < i) {
    k*=2; j++;
  } //k is the total number of permutations

  struct {
    int b, L, R;
    float c;
  } A[k];
  for (j = 1; j < k; j++) {
    A[j].b = 0;
    A[j].L = 0;
    A[j].R = 0;

    h = k / 2;
    g = j;
    while (h > 0) {
      if(g >= h) {
        g %= h;
        s[m] = 1;
        m++;
      } else{
        s[m]=0;m++;
      }
      h /= 2;
    }

  for(m = 0; m < 10; m++){
    if ( s[m]==1 ){
    l++;
    q*=arr[i-m];//q is the combined selectivity for j
    s[m]=0;}
  }//l is the number of basic terms for j
  qq=q;//q always less than 0.5
  if (q > 0.5) {
    q = (1 - q);
  }
  
  A[j].c = l * arr2[0] + (l-1) *arr2[2] + l * arr2[5] + arr2[1] + arr2[3] * q + arr2[4] * qq;//A[j].c returns the cost for "all-&" plan
  if (arr2[4] < (arr2[1] + arr2[3] * q + arr2[4] * qq)) {
    A[j].b=1;//this denotes that no-branch plan is better
  }

  l=0;m=0;//initialize l and m to be 0
  }//end for j, this loop returns cost for all-& plan and also denotes situations in which no-branching is better

  for (j = 1; j < k - 1; j++){//j refers to the right child
    h = k / 2;
    g = j;
    while (h > 0) {
      if (g >= h) {
        g%=h;
        r[m]=1;//denote the basci term is on
        m++;
      } else {
        r[m]=0;//denote the basic term is off
        m++;
      }
      h /= 2;
    }//this loop returns the appearance of certain basic term in right child
    
    for (m = 0; m < 10; m++) {
      if(r[m]==1){
      l++;//denote the number of basic terms
      p2*=arr[i-m];}//p2 is the combined selectivity of right child
    }
    fcost2 = (l * arr2[0]) + ((l - 1)* arr2[2]) + l * arr2[5] + arr2[1];
    for(p = 1; p < k - 1; p++) {//p refers to the left child
      h = k / 2;
      g = p;
      while (h > 0) {
        if (g >= h) {
          g %= h;
          t[n]=1;
          n++;
        } else {
          t[n]=0;
 	  n++;
        }
        h /= 2;
      }
      for (n=0; n < 10; n++){
        if (t[n] == 1) {
        ll++;
        p1 *= arr[i-n];
        }
      }
      fcost1 = (ll * arr2[0]) + ((ll - 1) * arr2[2]) + ll * arr2[5] + arr2[1];
      if (p1 > 0.5) {
        b = 1 - p1;
      } else {
        b = p1; 
      }//b is always less than 0.5
      
      for(a = 0;a < i; a++) {
        if ((r[a] == 1) && (t[a] == 1)) {
          flag = 1;//flag=1 means the left child and right child are not compatible
	  break;
	}
      }
      if ( flag == 1) {
        flag = 0;//initialization
        continue;//no && plan considered for this case
      } else if ((p2 <= p1) && ((fcost2 - fcost1 + p2 * fcost1 - p1 * fcost2) < 0)) {
        continue;//no && plan considered
      } else if (((p1 <= 0.5) && (p2 < p1)) && (fcost2 < fcost1)) {
        continue;//no && plan considered
      } else if ((fcost1 + arr2[3] * b + p1 * A[j].c) < A[j + p].c) {//consider && plan
        A[j+p].c=fcost1 + arr2[3] * b + p1 * A[j].c;
        A[j+p].L=p;
        A[j+p].R=j;
      }
      for(y = 0; y < 10; y ++) {t[y]=0;}
      ll = 0; n = 0; p1 = 1;
    }//end for p
  for(y = 0; y < 10; y ++) {r[y]=0;}
  l = 0; m = 0; p2 = 1;
  }//end for j, this loop consider && plan
  if(A[k-1].L==0) {//means no &&
    if(A[k-1].b==0) {//means no no-branching
      printf("if(t1[o1[i]]");
      for(c = 2;c <= i;c ++) {printf(" & t%d[o%d[i]])", c, c);}
      printf("){\n  answer[j++] = i;\n}");
    }
    else {//means there is no-branching
      printf("  answer[j] = i;\n  j += (t1[o1[i]]");
      for(c = 2;c <= i;c ++) {printf(" & t%d[o%d[i]]", c, c);}
      printf(");\n");
    }  
  } else {//means there is &&
	  printf("if(");
	  lll[0] = A[k - 1].L;
	  lll[1] = A[k - 1].R;
	  rr[0] = k - 1;
	  count = 2;
	  max = count;
	  for (l = 2; ;l += 2) {
		  lll[l] = A[lll[l / 2 - 1]].L; lll[l + 1] = A[lll[l / 2 - 1]].R; if( lll[l] != 0) {count ++; if (lll[l/2-1]) rr[l / 2] = lll[l / 2 - 1]; else rr[l/2]=lll[l/2+1]; if (max < count) max = count;} else {count --; if (lll[l/2-1]) rr[l / 2] = lll[l / 2 - 1]; else rr[l/2]=lll[l/2+1];}
          if (count == 0) break;
	  }
	  for (m = 0; m < l + 2; m++) {
                  if ((lll[m] == 0) && (m % 4 == 0)) {a=lll[m - 3]; break;}
          }
	  if (A[a].b!= 0) {//means no no-branching for the last &-term
		  for (m = 0; m < l + 2; m ++){
			  if (lll[m] == 0 && m % 4 == 0) {m ++; continue;}
			  if (lll[m] == 0 && m % 4 != 0) {printf("("); output(rr[m / 2]); m ++; break;}
		  }
		  for (m = m + 1; m < l + 2; ){
                          if (lll[m] == 0 && m % 4 == 0) {m += 2; continue;}
			  if (lll[m] == 0 && m % 4 != 0) {printf(" && ("); output(rr[m / 2]); m += 2; break;}
		  }
		  for (m = m + 1; m < l + 2; m ++){
			  if (lll[m] == 0 && m % 4 == 0) {m ++; continue;}
			  if (lll[m] == 0 && m % 4 != 0) {printf(" && "); output(rr[m / 2]); m ++;}
		  }
		  for (n = m; n > 0; n --) {
			  if (lll[n] == 0 && n % 4 != 0) {n --; continue;}
		          if (lll[n] == 0 && n % 4 == 0) {printf(" && "); output(rr[n / 2]); printf(")"); n --;}
		  }
		  printf(" {\n  answer[j++] = i;\n}");
	  } else {//means no-branching for the last &-term
//                  printf("%d,%d,", A[k-1].L, A[k-1].R);
//		  for (m = 0; m < l + 2; m ++) {printf("%d ",lll[m]);} puts("\n");
//                for (m = 0; m < l + 2; m ++) {printf("%d ", rr [m]);}
		  for (m = 0; m < l + 2; m ++){
			  if (lll[m] == 0 && m % 4 == 0) {m ++; continue;}
			  if (lll[m] == 0 && m % 4 != 0) {printf("("); output(rr[m / 2]); m ++; max --; break;}
		  }
		  for (m = m + 1; m < l + 2; m ++){
			  if (max == 1) break;
			  else {if (lll[m] == 0 && m % 4 == 0) {m ++; continue;}
			        if (lll[m] == 0 && m % 4 != 0) {printf(" && ("); output(rr[m / 2]); m ++; max --; break;}}
		  }
		  for (m = m + 1; m < l + 2; m ++){
			  if (lll[m] == 0 && m % 4 == 0) {m ++; continue;}
                          if (lll[m] == 0 && m % 4 != 0) {printf(" && "); output(rr[m / 2]); m ++;}
                  }
		  for (n = l; n > 0; n --) {
                          if (lll[n] == 0 && n % 4 == 0) {if (max == 0) break ; printf(" &&"); output(rr[n / 2]); printf(")"); max --;}
			  if (lll[n] == 0 && n % 4 != 0) if (max == 0) break;
		          n --;
                  }
		  printf("{\n  answer[j] == i;\n  j += ");
		  output(a);
		  printf(";\n}");
	  }
  }
  return A[k-1].c;//retunrs the final cost
}

int main(int argc, char * argv[]) {

  FILE * fp;

  int line = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  int m=0;
  int n=0;

  char str[1024] = {0};
  int cost[10] = {0};
  float arr[10][10] = {0}, x=0;
  int arr2[6] = {0};

  fp = fopen(argv[1],"r");

  // for each line of the file. 
  while(!feof(fp)){
    char *p;

    if (fgets(str,sizeof(str), fp) == NULL) {
      break;
    }

    line++;

    p = strtok(str," ");

    while(p){
      arr[i][j++]=atof(p);
      p=strtok(NULL," ");
    }

    while( j < 10) {
      arr[i][j++]=1.1;
    }
    i++;
    j=0;
  }
  fclose(fp);
  fp = fopen(argv[2],"r");
  while(!feof(fp)){
    char *p;
    if(fgets(str,sizeof(str),fp)==NULL) break;
    p=strtok(str,"= ");
    while(p){
      p=strtok(NULL,"= ");
      arr2[k++]=atoi(p);
      p=strtok(NULL,"= ");
    }
  }
  fclose(fp);
  printf("===================================================\n");
  for (m = 0; m < line; m++) {
    for(n = 0; n < 10; n++){
      if (arr[m][n]>1) {
        break;
      }
      printf("%.2f ", arr[m][n]);
    }
    printf("\n---------------------------------------------------\n");
    x = code(arr[m],arr2);
    printf("\n\n\n\n\n");
    printf("---------------------------------------------------\n");
    printf("cost:%.2f\n", x);
    printf("===================================================\n");
  }
  return 0;
}
