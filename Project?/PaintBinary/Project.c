//
//  Project.c
//  
//
//  Created by Jerry Zhu on 2019-02-21.
//

#include "Project.h"
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdio.h>


int p1page = 0;
int p2page = 0;
int ballpage = 1;
int ballc = 63;
int x;
int y;
char score[] = "0:0";
int upordown;
int timeoutcount = 0;
int scoreornot = 0;
int timer3count = 0;
int level = 0;
char textstring[] = "text, more text, and even more text!";
char highscorestring0[16];
char highscorestring1[16];
char highscorestring2[16];
char highscorestring3[16];
int mytime = 0x0000;
int highscoretime[] = {3599,3599,3599,3599};
int totaltime = 0;

char textbuffer[4][16];

const uint8_t const font[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 94, 0, 0, 0, 0,
    0, 0, 4, 3, 4, 3, 0, 0,
    0, 36, 126, 36, 36, 126, 36, 0,
    0, 36, 74, 255, 82, 36, 0, 0,
    0, 70, 38, 16, 8, 100, 98, 0,
    0, 52, 74, 74, 52, 32, 80, 0,
    0, 0, 0, 4, 3, 0, 0, 0,
    0, 0, 0, 126, 129, 0, 0, 0,
    0, 0, 0, 129, 126, 0, 0, 0,
    0, 42, 28, 62, 28, 42, 0, 0,
    0, 8, 8, 62, 8, 8, 0, 0,
    0, 0, 0, 128, 96, 0, 0, 0,
    0, 8, 8, 8, 8, 8, 0, 0,
    0, 0, 0, 0, 96, 0, 0, 0,
    0, 64, 32, 16, 8, 4, 2, 0,
    0, 62, 65, 73, 65, 62, 0, 0,
    0, 0, 66, 127, 64, 0, 0, 0,
    0, 0, 98, 81, 73, 70, 0, 0,
    0, 0, 34, 73, 73, 54, 0, 0,
    0, 0, 14, 8, 127, 8, 0, 0,
    0, 0, 35, 69, 69, 57, 0, 0,
    0, 0, 62, 73, 73, 50, 0, 0,
    0, 0, 1, 97, 25, 7, 0, 0,
    0, 0, 54, 73, 73, 54, 0, 0,
    0, 0, 6, 9, 9, 126, 0, 0,
    0, 0, 0, 102, 0, 0, 0, 0,
    0, 0, 128, 102, 0, 0, 0, 0,
    0, 0, 8, 20, 34, 65, 0, 0,
    0, 0, 20, 20, 20, 20, 0, 0,
    0, 0, 65, 34, 20, 8, 0, 0,
    0, 2, 1, 81, 9, 6, 0, 0,
    0, 28, 34, 89, 89, 82, 12, 0,
    0, 0, 126, 9, 9, 126, 0, 0,
    0, 0, 127, 73, 73, 54, 0, 0,
    0, 0, 62, 65, 65, 34, 0, 0,
    0, 0, 127, 65, 65, 62, 0, 0,
    0, 0, 127, 73, 73, 65, 0, 0,
    0, 0, 127, 9, 9, 1, 0, 0,
    0, 0, 62, 65, 81, 50, 0, 0,
    0, 0, 127, 8, 8, 127, 0, 0,
    0, 0, 65, 127, 65, 0, 0, 0,
    0, 0, 32, 64, 64, 63, 0, 0,
    0, 0, 127, 8, 20, 99, 0, 0,
    0, 0, 127, 64, 64, 64, 0, 0,
    0, 127, 2, 4, 2, 127, 0, 0,
    0, 127, 6, 8, 48, 127, 0, 0,
    0, 0, 62, 65, 65, 62, 0, 0,
    0, 0, 127, 9, 9, 6, 0, 0,
    0, 0, 62, 65, 97, 126, 64, 0,
    0, 0, 127, 9, 9, 118, 0, 0,
    0, 0, 38, 73, 73, 50, 0, 0,
    0, 1, 1, 127, 1, 1, 0, 0,
    0, 0, 63, 64, 64, 63, 0, 0,
    0, 31, 32, 64, 32, 31, 0, 0,
    0, 63, 64, 48, 64, 63, 0, 0,
    0, 0, 119, 8, 8, 119, 0, 0,
    0, 3, 4, 120, 4, 3, 0, 0,
    0, 0, 113, 73, 73, 71, 0, 0,
    0, 0, 127, 65, 65, 0, 0, 0,
    0, 2, 4, 8, 16, 32, 64, 0,
    0, 0, 0, 65, 65, 127, 0, 0,
    0, 4, 2, 1, 2, 4, 0, 0,
    0, 64, 64, 64, 64, 64, 64, 0,
    0, 0, 1, 2, 4, 0, 0, 0,
    0, 0, 48, 72, 40, 120, 0, 0,
    0, 0, 127, 72, 72, 48, 0, 0,
    0, 0, 48, 72, 72, 0, 0, 0,
    0, 0, 48, 72, 72, 127, 0, 0,
    0, 0, 48, 88, 88, 16, 0, 0,
    0, 0, 126, 9, 1, 2, 0, 0,
    0, 0, 80, 152, 152, 112, 0, 0,
    0, 0, 127, 8, 8, 112, 0, 0,
    0, 0, 0, 122, 0, 0, 0, 0,
    0, 0, 64, 128, 128, 122, 0, 0,
    0, 0, 127, 16, 40, 72, 0, 0,
    0, 0, 0, 127, 0, 0, 0, 0,
    0, 120, 8, 16, 8, 112, 0, 0,
    0, 0, 120, 8, 8, 112, 0, 0,
    0, 0, 48, 72, 72, 48, 0, 0,
    0, 0, 248, 40, 40, 16, 0, 0,
    0, 0, 16, 40, 40, 248, 0, 0,
    0, 0, 112, 8, 8, 16, 0, 0,
    0, 0, 72, 84, 84, 36, 0, 0,
    0, 0, 8, 60, 72, 32, 0, 0,
    0, 0, 56, 64, 32, 120, 0, 0,
    0, 0, 56, 64, 56, 0, 0, 0,
    0, 56, 64, 32, 64, 56, 0, 0,
    0, 0, 72, 48, 48, 72, 0, 0,
    0, 0, 24, 160, 160, 120, 0, 0,
    0, 0, 100, 84, 84, 76, 0, 0,
    0, 0, 8, 28, 34, 65, 0, 0,
    0, 0, 0, 126, 0, 0, 0, 0,
    0, 0, 65, 34, 28, 8, 0, 0,
    0, 0, 4, 2, 4, 2, 0, 0,
    0, 120, 68, 66, 68, 120, 0, 0,
};


uint8_t  bgm[] = {
    //page0
    0,0,0,255,255,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,255,255,0,0,0,
    
    //page1
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,56,56,56,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    
    //page2
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    
    //page3
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
};

uint8_t  bginit[] = {
    //page0
    0,0,0,255,255,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,255,255,0,0,0,
    
    //page1
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,56,56,56,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    
    //page2
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    
    //page3
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
};

/* Declare a helper function which is local to this file */
static void num32asc( char * s, int );

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* Non-Maskable Interrupt; something bad likely happened, so hang */
void _nmi_handler() {
    for(;;);
}

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset() {
    
}

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap() {
    
}

/* quicksleep:
 A simple function to create a small delay.
 Very inefficient use of computing resources,
 but very handy in some special cases. */
void quicksleep(int cyc) {
    int i;
    for(i = cyc; i > 0; i--);
}

/* tick:
 Add 1 to time in memory, at location pointed to by parameter.
 Time is stored as 4 pairs of 2 NBCD-digits.
 1st pair (most significant byte) counts days.
 2nd pair counts hours.
 3rd pair counts minutes.
 4th pair (least significant byte) counts seconds.
 In most labs, only the 3rd and 4th pairs are used. */
void tick( unsigned int * timep )
{
    /* Get current value, store locally */
    register unsigned int t = * timep;
    t += 1; /* Increment local copy */
    
    /* If result was not a valid BCD-coded time, adjust now */
    
    if( (t & 0x0000000f) >= 0x0000000a ) t += 0x00000006;
    if( (t & 0x000000f0) >= 0x00000060 ) t += 0x000000a0;
    /* Seconds are now OK */
    
    if( (t & 0x00000f00) >= 0x00000a00 ) t += 0x00000600;
    if( (t & 0x0000f000) >= 0x00006000 ) t += 0x0000a000;
    /* Minutes are now OK */
    
    if( (t & 0x000f0000) >= 0x000a0000 ) t += 0x00060000;
    if( (t & 0x00ff0000) >= 0x00240000 ) t += 0x00dc0000;
    /* Hours are now OK */
    
    if( (t & 0x0f000000) >= 0x0a000000 ) t += 0x06000000;
    if( (t & 0xf0000000) >= 0xa0000000 ) t = 0;
    /* Days are now OK */
    
    * timep = t; /* Store new value */
}



//draw
uint8_t spi_send_recv(uint8_t data) {
    while(!(SPI2STAT & 0x08));
    SPI2BUF = data;
    while(!(SPI2STAT & 1));
    return SPI2BUF;
}

//set up
void display_init(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    quicksleep(10);
    DISPLAY_ACTIVATE_VDD;
    quicksleep(1000000);
    
    spi_send_recv(0xAE);
    DISPLAY_ACTIVATE_RESET;
    quicksleep(10);
    DISPLAY_DO_NOT_RESET;
    quicksleep(10);
    
    spi_send_recv(0x8D);
    spi_send_recv(0x14);
    
    spi_send_recv(0xD9);
    spi_send_recv(0xF1);
    
    DISPLAY_ACTIVATE_VBAT;
    quicksleep(10000000);
    
    spi_send_recv(0xA1);
    spi_send_recv(0xC8);
    
    spi_send_recv(0xDA);
    spi_send_recv(0x20);
    
    spi_send_recv(0xAF);
}

void display_string(int line, char *s) {
    int i;
    if(line < 0 || line >= 4)
        return;
    if(!s)
        return;
    
    for(i = 0; i < 16; i++)
        if(*s) {
            textbuffer[line][i] = *s;
            s++;
        } else
            textbuffer[line][i] = ' ';
}

void display_image(int x, const uint8_t *data) {
    int i, j;
    
    for(i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        
        spi_send_recv(0x22);
        spi_send_recv(i);
        
        spi_send_recv(x & 0xF);
        spi_send_recv(0x10 | ((x >> 4) & 0xF));
        
        DISPLAY_CHANGE_TO_DATA_MODE;
        
        for(j = 0; j < 128; j++)
            spi_send_recv(data[i*128 + j]);
    }
}

void display_update(void) {
    int i, j, k;
    int c;
    for(i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_recv(0x22);
        spi_send_recv(i);
        
        spi_send_recv(0x0);
        spi_send_recv(0x10);
        
        DISPLAY_CHANGE_TO_DATA_MODE;
        
        for(j = 0; j < 16; j++) {
            c = textbuffer[i][j];
            if(c & 0x80)
                continue;
            
            for(k = 0; k < 8; k++)
                spi_send_recv(font[c*8 + k]);
        }
    }
}

//player movement
void p1up (){
    if (p1page != 0){
        int i;
        for (i=0; i<2; i++){
            bgm[p1page * 128 + 3 + i] = 0;
            bgm[(p1page - 1) * 128 + 3 + i] = 255;
        }
        p1page --;
        display_image(0,bgm);
    }
}

//player movement
void p1down (){
    if (p1page != 3){
        int i;
        for (i=0; i<2; i++){
            bgm[p1page * 128 + 3 + i] = 0;
            bgm[(p1page + 1) * 128 + 3 + i] = 255;
        }
        p1page ++;
        display_image(0,bgm);
    }
}

//player movement
void p2up (){
    if (p2page != 0){
        int i;
        for (i=0; i<2; i++){
            bgm[p2page * 128 + 123 + i] = 0;
            bgm[(p2page - 1) * 128 + 123 + i] = 255;
        }
        p2page --;
        display_image(0,bgm);
    }
}

//player movement
void p2down(){
    if (p2page != 3){
        int i;
        for (i=0; i<2; i++){
            bgm[p2page * 128 + 123 + i] = 0;
            bgm[(p2page + 1) * 128 + 123 + i] = 255;
        }
        p2page ++;
        display_image(0,bgm);
    }
}

void fball (){
    if (ballc < 121){
        bgm[(ballpage - 1) * 128 + ballc + 2] = bgm[(ballpage - 1) * 128 + ballc - 1];
        bgm[ballpage * 128 + ballc + 2] = bgm[ballpage * 128 + ballc - 1];
        bgm[(ballpage + 1) * 128 + ballc + 2] = bgm[(ballpage + 1) * 128 + ballc - 1];
        
        bgm[(ballpage - 1) * 128 + ballc - 1] = 0;
        bgm[ballpage * 128 + ballc - 1] = 0;
        bgm[(ballpage + 1) * 128 + ballc - 1] = 0;
        
        ballc ++;
        
        display_image(0,bgm);
        quicksleep(50000);
    }
}

void bball(){
    if (ballc > 6){
        bgm[(ballpage - 1) * 128 + ballc - 2] = bgm[(ballpage - 1) * 128 + ballc + 1];
        bgm[ballpage * 128 + ballc - 2] = bgm[ballpage * 128 + ballc + 1];
        bgm[(ballpage + 1) * 128 + ballc - 2] = bgm[(ballpage + 1) * 128 + ballc + 1];
        
        bgm[(ballpage - 1) * 128 + ballc + 1] = 0;
        bgm[ballpage * 128 + ballc + 1] = 0;
        bgm[(ballpage + 1) * 128 + ballc + 1] = 0;
        
        ballc --;
        
        display_image(0,bgm);
        quicksleep(50000);
    }
}

void uball(){
    if (ballpage != 1 || (ballpage == 1 && bgm[128+ ballc] > 7)){
        if (bgm[ballpage * 128 + ballc] == 7){
            bgm[(ballpage - 1) * 128 + ballc] = 128;
            bgm[ballpage * 128 + ballc] /= 2;
            bgm[(ballpage - 1) * 128 + ballc - 1] = 128;
            bgm[(ballpage - 1) * 128 + ballc + 1] = 128;
            bgm[ballpage * 128 + ballc - 1] /= 2;
            bgm[ballpage * 128 + ballc + 1] /= 2;
            
            display_image(0,bgm);
            quicksleep(50000);
            return;
        }
        
        if (bgm[ballpage * 128 + ballc] == 3){
            bgm[(ballpage - 1) * 128 + ballc] = 192;
            bgm[ballpage * 128 + ballc] /= 2;
            bgm[(ballpage - 1) * 128 + ballc - 1] = 192;
            bgm[(ballpage - 1) * 128 + ballc + 1] = 192;
            bgm[ballpage * 128 + ballc - 1] /= 2;
            bgm[ballpage * 128 + ballc + 1] /= 2;
            ballpage --;
            
            display_image(0,bgm);
            quicksleep(50000);
            return;
        }
        
        if (bgm[ballpage * 128 + ballc] == 192){
            bgm[ballpage * 128 + ballc] = 224;
            bgm[(ballpage + 1) * 128 + ballc] = 0;
            bgm[ballpage * 128 + ballc - 1] = 224;
            bgm[ballpage * 128 + ballc + 1] = 224;
            bgm[(ballpage + 1) * 128 + ballc - 1] = 0;
            bgm[(ballpage + 1) * 128 + ballc + 1] = 0;
            
            display_image(0,bgm);
            quicksleep(50000);
            return;
        }
        
        bgm[ballpage * 128 + ballc] /= 2;
        bgm[ballpage * 128 + ballc - 1] /= 2;
        bgm[ballpage * 128 + ballc + 1] /= 2;
        
        display_image(0,bgm);
        quicksleep(50000);
    }
}

void dball(){
    if (ballpage != 3 || (ballpage == 3 && bgm[3*128 + ballc] < 224)){
        if (bgm[ballpage * 128 + ballc] == 224){
            bgm[ballpage * 128 + ballc] = 192;
            bgm[(ballpage + 1) * 128 + ballc] = 1;
            bgm[ballpage * 128 + ballc - 1] = 192;
            bgm[ballpage * 128 + ballc + 1] = 192;
            bgm[(ballpage + 1) * 128 + ballc - 1] = 1;
            bgm[(ballpage + 1) * 128 + ballc + 1] = 1;
            
            display_image(0,bgm);
            quicksleep(50000);
            return;
        }
        
        if (bgm[ballpage * 128 + ballc] == 192){
            bgm[ballpage * 128 + ballc] = 128;
            bgm[(ballpage + 1) * 128 + ballc] = 3;
            bgm[ballpage * 128 + ballc - 1] = 128;
            bgm[ballpage * 128 + ballc + 1] = 128;
            bgm[(ballpage + 1) * 128 + ballc - 1] = 3;
            bgm[(ballpage + 1) * 128 + ballc + 1] = 3;
            ballpage++;
            
            display_image(0,bgm);
            quicksleep(50000);
            return;
        }
        
        if (bgm[ballpage * 128 + ballc] == 3){
            bgm[(ballpage - 1) * 128 + ballc] = 0;
            bgm[ballpage * 128 + ballc] = 7;
            bgm[(ballpage - 1) * 128 + ballc - 1] = 0;
            bgm[(ballpage - 1) * 128 + ballc + 1] = 0;
            bgm[ballpage * 128 + ballc - 1] = 7;
            bgm[ballpage * 128 + ballc + 1] = 7;
            
            display_image(0,bgm);
            quicksleep(50000);
            return;
        }
        
        bgm[ballpage * 128 + ballc] *= 2;
        bgm[ballpage * 128 + ballc - 1] *= 2;
        bgm[ballpage * 128 + ballc + 1] *= 2;
        
        display_image(0,bgm);
        quicksleep(50000);
    }
}

void rulesh(){
    
    if (ballc == 6 && p1page == ballpage){
        x = 1;
        return;
    }
    
    if (ballc == 6 && p1page != ballpage){
        display_string(0, "Congragulations!");
        display_string(1, "Player2Scores");
        score[2]++;
        display_string(2,score);
        display_string(3, "GameResumesSoon");
        display_update();
        delay(1000);
        delay(1000);
        
        
        int i;
        for (i=0; i<4*128; i++){
            bgm[i]=bginit[i];
        }
        display_image(0,bgm);
        scoreornot = 1;
        
        return;
    }
    
    if (ballc == 121 && p2page == ballpage){
        x = 0;
        return;
    }
    
    if (ballc == 121 && p2page != ballpage){
        display_string(0, "Congragulations!");
        display_string(1, "Player1Scores");
        score[0]++;
        display_string(2,score);
        display_string(3, "GameResumesSoon");
        display_update();
        delay(1000);
        delay(1000);
       
        int i;
        for (i=0;i<4*128;i++){
            bgm[i]=bginit[i];
        }
        display_image(0,bgm);
        scoreornot = 1;
        
        return;
    }
    
}

void rulesv() {
    
    if (ballpage == 1 && bgm[128+ballc] == 7){
        y = 0;
        return;
    }
    
    if (ballpage == 3 && bgm[3 * 128 + ballc] == 224){
        y = 1;
        return;
    }
    
}

int serveball(){
    int random;
    random = TMR2 % 4;
    return random;
}

int serveball2(){
    int random;
    random = TMR3 % 4;
    return random;
}

int iq(){
    int random;
    random = TMR3 % 100;
    return random;
}

int getbtns (void){
    int n = (PORTD >> 4) & 0xe;
    int m = (PORTF >> 1) & 0x1;
    int k = n + m;
    quicksleep(200000);
    
    return k;
}

void workdouble(){
    
    display_image(0, bgm);
    
    int rng;
    
    timeoutcount = 0;
    
    while (score[0] < 53 && score[2] < 53){
        T2CON = 0x8070;
        rng = serveball();
        
        if (rng == 0){
            x=0;
            y=0;
        }
        
        if (rng == 1){
            x=0;
            y=1;
        }
        
        if (rng == 2){
            x=1;
            y=0;
        }
        
        if (rng == 3){
            x=1;
            y=1;
        }
        
        while (scoreornot == 0){
            
            if (IFS(0) & 0x100){
                timeoutcount++;
                
                if(timeoutcount==5){
                    
                    int btns = getbtns();
                    
                    if(btns & 0x8){
                        p1up();
                    }
                    
                    if(btns & 0x4){
                        p1down();
                    }
                    
                    if(btns & 0x2){
                        p2up();
                    }
                    
                    if(btns & 0x1){
                        p2down();
                    }
                    
                    timeoutcount = 0;
                }
                IFSCLR(0) = 0x100;
            }
            
            if (x==0){
                bball();
                rulesh();
            }

            if (x==1){
                fball();
                rulesh();
            }
            
            if (y==0){
                dball();
                rulesv();
            }
            
            if (y==1){
                uball();
                rulesv();
            }
        }
        scoreornot = 0;
        p1page = 0;
        p2page = 0;
        ballpage = 1;
        ballc = 63;
    }
    
    T2CON = 0;
    
    display_string(0,"GameIsOver");
    if (score[0]==53)
        display_string(1,"Player1Wins!");
    else
        display_string(1,"Player2Wins!");
    display_string(2,score);
    
    score[0] = 48;
    score[1] = 58;
    score[2] = 48;
    
    display_string(3,"BackToMenuSoon");
    display_update();
    
    delay(1000);
    delay(1000);
    
    display_string(0, "WelcomeToPong");
    display_string(1, "SinglePlayer");
    display_string(2, "MultiplePlayer");
    display_string(3, "Highscore");
    display_update();
}

void timecompare (int timebuffer){
    
    int i;
    
    if (timebuffer < highscoretime[3]){
        highscoretime[3] = timebuffer;
    }
    
    int a;
    
    for(i=2;i>=0;i--){
        if(highscoretime[i] > highscoretime[i+1]){
            a = highscoretime[i];
            highscoretime[i] = highscoretime[i+1];
            highscoretime[i+1] = a;
        }
    }
}

void worksingle(){
    
    display_image(0, bgm);
    
    totaltime = 0;
    mytime = 0x0000;
    timer3count = 0;
    
    T3CON = 0;
    PR3 = ((80000000/256)/10);
    TMR3 = 0;
    
    T3CON = 0x8070;
  
    while(score[0]<53 && score[2]<53){
        int rng;
        
        int ai;
        
        rng = serveball2();
        
        if (rng == 0){
            x=0;
            y=0;
        }
        
        if (rng == 1){
            x=0;
            y=1;
        }
        
        if (rng == 2){
            x=1;
            y=0;
        }
        
        if (rng == 3){
            x=1;
            y=1;
        }
        
        while (scoreornot == 0){
            
            if (IFS(0) & 0x1000){
                
                timer3count ++;
                
                if(timer3count % 5 ==0){
                    
                    int btns = getbtns();
                    
                    if(btns & 0x8){
                        p1up();
                    }
                    
                    if(btns & 0x4){
                        p1down();
                    }
                }
                
                if(timer3count % 10 == 0){
                    totaltime ++;
                }
                    
                if(timer3count % 200 == 0){
                    if (level < 2)
                        level++;
                }
                
                IFSCLR(0) = 0x1000;
            }
            
            if (x==0){
                bball();
                rulesh();
            }
            
            if (x==1){
                fball();
                rulesh();
            }
            
            if (y==0){
                dball();
                rulesv();
            }
            
            if (y==1){
                uball();
                rulesv();
            }
            
            if (level == 0){
                ai = iq();
                if (ai < 5){
                    int pagedifference;
                    pagedifference = p2page - ballpage;
                    while (pagedifference > 0){
                        p2up();
                        pagedifference --;
                        quicksleep(50000);
                    }
                    while (pagedifference < 0){
                        p2down();
                        pagedifference ++;
                        quicksleep(50000);
                    }
                }
            }
            else if (level == 1){
                ai = iq();
                if (ai < 10){
                    int pagedifference;
                    pagedifference = p2page - ballpage;
                    while (pagedifference > 0){
                        p2up();
                        pagedifference --;
                        quicksleep(50000);
                    }
                    while (pagedifference < 0){
                        p2down();
                        pagedifference ++;
                        quicksleep(50000);
                    }
                }
            }
            else if (level == 2){
                ai = iq();
                if (ai < 20){
                    int pagedifference;
                    pagedifference = p2page - ballpage;
                    while (pagedifference > 0){
                        p2up();
                        pagedifference --;
                        quicksleep(50000);
                    }
                    while (pagedifference < 0){
                        p2down();
                        pagedifference ++;
                        quicksleep(50000);
                    }
                }
            }
        }
        scoreornot = 0;
        p1page = 0;
        p2page = 0;
        ballpage = 1;
        ballc = 63;
    }
    
    T3CON = 0;
    level = 0;
    
    if (score[0]==53){

        int i;
        for (i=0; i<totaltime; i++)
            tick( &mytime );
        
        time2string( textstring, mytime );
        
        display_string(0,"Amazing!");
        display_string(1,"YouAreTheHero!");
        display_string(2,"YourTimeWas:");
        display_string(3, textstring);
        display_update();
        
        timecompare(totaltime);
    }

    else if (score[2] == 53){
        
        int i;
        for (i=0; i<totaltime; i++)
            tick( &mytime );
        
        time2string( textstring, mytime );
        
        display_string(0,"ItWasSoClose!");
        display_string(1,"Don'tGiveUp!");
        display_string(2,"YourTimeWas:");
        display_string(3, textstring );
        display_update();
    }
 
    score[0] = 48;
    score[1] = 58;
    score[2] = 48;
    
    delay(1);
    delay(1);
    delay(1);
    
    display_string(0, "WelcomeToPong");
    display_string(1, "SinglePlayer");
    display_string(2, "MultiplePlayer");
    display_string(3, "Highscore");
    display_update();
}

void displaymode(){
    if (upordown == 0){
        display_string(0, "WelcomeToPong<");
        display_string(1, "SinglePlayer");
        display_string(2, "MultiplePlayer");
        display_string(3, "Highscore");
        display_update();
    }
    
    if (upordown == 1){
        display_string(0, "WelcomeToPong");
        display_string(1, "SinglePlayer<");
        display_string(2, "MultiplePlayer");
        display_string(3, "Highscore");
        display_update();
    }
    
    if (upordown == 2){
        display_string(0, "WelcomeToPong");
        display_string(1, "SinglePlayer");
        display_string(2, "MultiplePlayer<");
        display_string(3, "Highscore");
        display_update();
    }
    
    if (upordown == 3){
        display_string(0, "WelcomeToPong");
        display_string(1, "SinglePlayer");
        display_string(2, "MultiplePlayer");
        display_string(3, "Highscore<");
        display_update();
    }
    
}

int choosemode(){
    
    upordown = 0;
    
    
    display_string(0, "WelcomeToPong<");
    display_string(1, "SinglePlayer");
    display_string(2, "MultiplePlayer");
    display_string(3, "Highscore");
    display_update();
    
    while(1){
        
        if (getbtns() & 0x8){
            if (upordown > 0){
                upordown --;
                displaymode();
            }
        }
        
        if (getbtns() & 0x4){
            if (upordown < 3){
                upordown ++;
                displaymode();
            }
        }
        
        if (getbtns() & 0x2){
            break;
        }
    }
    
    if (upordown == 1){
        return 1;
    }
    if (upordown == 2){
        return 2;
    }
    if (upordown == 3){
        return 3;
    }
}

int main(void){

    /*
     This will set the peripheral bus clock to the same frequency
     as the sysclock. That means 80 MHz, when the microcontroller
     is running at 80 MHz. Changed 2017, as recommended by Axel.
     */
    SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
    SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
    while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
    OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
    while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
    SYSKEY = 0x0;  /* Lock OSCCON */
    
    /* Set up output pins */
    AD1PCFG = 0xFFFF;
    ODCE = 0x0;
    TRISECLR = 0xFF;
    PORTE = 0x0;
    
    /* Output pins for display signals */
    PORTF = 0xFFFF;
    PORTG = (1 << 9);
    ODCF = 0x0;
    ODCG = 0x0;
    TRISFCLR = 0x70;
    TRISGCLR = 0x200;
    
    /* Set up input pins */
    TRISDSET = (1 << 8);
    TRISFSET = (1 << 1);
    
    /* Set up SPI as master */
    SPI2CON = 0;
    SPI2BRG = 4;
    /* SPI2STAT bit SPIROV = 0; */
    SPI2STATCLR = 0x40;
    /* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
    /* SPI2CON bit MSTEN = 1; */
    SPI2CONSET = 0x20;
    /* SPI2CON bit ON = 1; */
    SPI2CONSET = 0x8000;

    
    
    display_init();
    display_string(0, "WelcomeToPong");
    display_string(1, "SinglePlayer");
    display_string(2, "MultiplePlayer");
    display_string(3, "Highscore");
    display_update();
    
    
    TRISD |= 0xfe0;
    TRISFSET = 0x2;
    
    while (1){
        
        delay(1000);
        delay(1000);
        
        int k = choosemode();
       
        if (k == 2){
            
            T2CON = 0;
            PR2 = ((80000000/256)/10);
            TMR2 = 0;
    
            workdouble();
            
        }
        else if (k == 1){
        
            worksingle();
            
        }
        else if (k == 3){
            int i,j;
            for (i=0; i<4; i++){
                mytime = 0x0000;
                for (j=0; j<highscoretime[i]; j++)
                    tick( &mytime );
                time2string(textstring, mytime);
                display_string(i, textstring);
            }
            display_update();
        }
    }
    return 0;
}

