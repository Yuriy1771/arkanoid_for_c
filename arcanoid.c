#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
// #include <ncurses.h>

#define WIDTH 65
#define HEIGHT 25

typedef struct {
    int x, y;
    int w;
}TRacket;

typedef struct {
    float x,y;
    int ix, iy;
    float alfa;
    float speed;
}TBall;

char mas[HEIGHT][WIDTH+1];

TRacket racket;
TBall ball;

int hitCount = 0;
int maxHitCount = 0;

void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int) round(ball.x);
    ball.iy = (int) round(ball.y);

}

void autoMoveBall() {
    if (ball.alfa < 0) ball.alfa += M_PI * 2;
    if(ball.alfa > M_PI * 2) ball.alfa -= M_PI * 2;

    TBall bl = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed,
    ball.y + sin(ball.alfa) * ball.speed);

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '=')) {
        if(mas[ball.iy][ball.ix] == '=') {
            hitCount++;
        }
        if((ball.ix != bl.ix) && (ball.iy != bl.iy)) {
          if(mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix]) {
              bl.alfa = bl.alfa + M_PI; 
          } else {
              if(mas[bl.iy][ball.ix] == '#') {
                  bl.alfa = (2 * M_PI - bl.alfa) + M_PI;
              } else {
                  bl.alfa = (2 * M_PI - bl.alfa);
              }
          }
        } else if (ball.iy == bl.iy) {
            bl.alfa = (2*M_PI - bl.alfa) + M_PI;
        } else {
            bl.alfa = (2 * M_PI - bl.alfa);
        }
        ball = bl;
        autoMoveBall();
    }
}

void initBall() {
    moveBall(racket.x + racket.w / 2, racket.y - 1);

    ball.alfa = -1;
    ball.speed = 1;
}
void putBall() {
    mas[ball.iy][ball.ix] = 'o';
}


void initRacket() {
    racket.w = 7;
    racket.x = (WIDTH - racket.w) / 2;
    racket.y = HEIGHT - 1;
}

void putRacket() {
    for(int i = racket.x; i < racket.x + racket.w; i++) {
        mas[racket.y][i] = '=';
    }
}

//отрисовка поля
void init() {
    for(int i = 0; i < WIDTH; i++) {
        mas[0][i] = '#';
        mas[0][WIDTH] = '\0';
    }
    strncpy(mas[1], mas[0], WIDTH+1);
    
        for(int i = 1; i < WIDTH-1; i++) {
            mas[1][i] = ' ';
        }

        for(int i = 2; i < HEIGHT; i++) {
            strncpy(mas[i], mas[1], WIDTH+1);  
        }
            
    // 1 lvl
    if(hitCount == 2) {
        printf("\n");
        for(int i = 10; i < 15; i++) {
            mas[i][10] = '#';
        }
    }
    //2 lvl
    if(hitCount > 2 && hitCount <= 4) {
        for(int i = 20; i < 50; i++) {
            mas[5][i] = '#';
        }
    }
    //3 lvl
     if(hitCount > 4 && hitCount <= 6) {
        for(int i = 40; i < 55; i++) {
            mas[15][i] = '#';
        }
    }
    //4 lvl
     if(hitCount > 6 && hitCount <= 8) {
        for(int i = 10; i < 20; i++) {
            mas[15][i] = '#';
            mas[7][i] = '#';
        }
    }
    //5 lvl
     if(hitCount > 8 && hitCount <= 10) {
        for(int i = 35; i < 40; i++) {
            mas[i][10] = '#';
            mas[i][15] = '#';
        }
    }
    
    
}

void show() {
    for(int i = 0; i < HEIGHT; i++) {
        printf("%s\n", mas[i]);
    }
      printf("                   hit %i", hitCount);
      printf("                   max %i \n", maxHitCount);

}

void moveRacket(int x) {
    racket.x = x;
    if(racket.x < 1) {
        racket.x = 1;
    }
    if(racket.x + racket.w >= WIDTH) {
        racket.x = WIDTH - 1 - racket.w;
    }
}



int main () {
    char key;
    bool run = false;
    initRacket();
    initBall();
do{
    system("clear");
    if (run) {
        autoMoveBall();
    }
    if (ball.iy > HEIGHT) {
        run = false;
        if(hitCount > maxHitCount) {
            maxHitCount = hitCount;
        }
        hitCount = 0;
    }
    init();
    putRacket();
    putBall();
    show();

    key = getchar();
    if(key == 'd') moveRacket(racket.x + 7);
    if(key == 'a') moveRacket(racket.x - 7);
    if(key == 'w') run = true;
    if(!run)
    moveBall(racket.x + racket.w / 2, racket.y - 1);
} while (key != 'e');

    return 0;
}