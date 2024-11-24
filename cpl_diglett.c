//sliding window

#include<stdio.h>

int n, m, d;
int table[705][705];

int record_x[100000];
int record_y[100000];
int count;

int initialize(int d) {
    int sum = 0;
    for(int k = 0; k <= d - 1; k++) {
        for (int i = d - k; i <= d + k; i++) {
            sum += table[k][i];
            sum += table[d + (d - k)][i];
        }
    }
    for (int i = 0; i <= d + d; i++) {
        sum += table[d][i];
    }
    return sum;

}

int UpAndDown(int *max, int sum, int i, int j, int d) {
    int temp_up = 0;
    int temp_down = 0;
    for (int r = 1; r <= d; r++) {
        temp_up += table[i - (d - r)][j - r];
        temp_up += table[i - (d - r)][j + r];
    }
    temp_up += table[i - d][j];
    for (int r = 1; r <= d; r++) {
        temp_down += table[i + 1 + (d - r)][j - r];
        temp_down += table[i + 1 + (d - r)][j + r];
    }
    temp_down += table[i + 1 + d][j];
    sum = sum - temp_up + temp_down;
    if(sum > *max) {
        *max = sum ;
        count = 1;
        record_x[count] = i - d + 2;
    record_y[count] = j - d + 1;
    }else if(sum == *max) {
        count++;
        record_x[count] = i - d + 2;
    record_y[count] = j - d + 1;
    }
    return sum ;
}

int main() {
    int sum = 0;
    int max_number = 0;
    int *max = &max_number;
    scanf("%d %d %d", &n, &m, &d);
    for (int i = d; i < d + n ; i++) {
        for(int j = d; j < d + m; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    sum = initialize(d);
*max = sum;
    int j = d;
    for(int i = d; i <= d + n - 1; i++ ) {
        if (j == d ) {
            while(j <= d + m - 2) {
                int tem_left = 0;
                int tem_right = 0;
                for (int r = 1; r <= d; r++) {
                    tem_left += table[i - r][j - (d - r)];
                    tem_left += table[i + r][j - (d - r)];
                }
                tem_left += table[i][j - d];
                for (int r = 1; r <= d; r++) {
                    tem_right += table[i - r][j + 1 +(d - r)];
                    tem_right += table[i + r][j + 1 +(d - r)];
                }
                tem_right += table[i][j + d + 1];
                sum = sum - tem_left + tem_right;
                if(sum > *max) {
                    *max = sum;
                    count = 1;
                    record_x[count] = i - d+ 1;
                record_y[count] = j - d + 2 ;
                }else if(*max == sum) {
                    count++;
                    record_x[count] = i - d + 1;
                record_y[count] = j - d + 2;
                }
                j++;
            }
            if(i == d + n - 1) break;
            sum = UpAndDown(max, sum, i, j, d);
        }
        else if(j == d + m - 1) {
            while(j >= d + 1) {
                int tem_left = 0;
                int tem_right = 0;
                for (int r = 1; r <= d; r++) {
                    tem_left += table[i - r][j - 1 - (d - r)];
                    tem_left += table[i + r][j - 1 - (d - r)];
                }
                tem_left += table[i][j - d - 1];
                for (int r = 1; r <= d; r++) {
                    tem_right += table[i - r][j + (d - r)];
                    tem_right += table[i + r][j + (d - r)];
                }
                tem_right += table[i][j + d];
                sum = sum - tem_right + tem_left;
                if(sum > *max) {
                    *max = sum;
                    count = 1;
                    record_x[count] = i - d + 1;
                record_y[count] = j - d;
                }else if(sum == *max) {
                    count++;
                    record_x[count] = i - d + 1;
                record_y[count] = j - d ;
                }
                
                j--;
            }
            if (i == n + d - 1) break ;
            sum = UpAndDown(max, sum, i, j, d);
        }
    }
    printf("%d %d\n",*max  ,count);
    for(int i = 1; i <= count; i++) {
        printf("%d %d\n",record_x[i],record_y[i]);
    }
    return 0;
}