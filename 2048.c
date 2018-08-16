#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

void mvUp(matrix * mtx, int col, int * score) {
    int i, j, cnt; 
    int changed = 0, nonzero = 0, new = 0, curr = 0;
    int *np, *cp;
    
    np = &new;
    cp = &curr;
   
    for (i = 0, cnt = 0; i <= 4; i++) {
        getElement(mtx, i, col, np);
        if (new != 0) {
            curr = 0;
            for (j = i - 1; j > 0; j--) {
                // Check for nonzero element below row i
                if (curr != 0) break;
                getElement(mtx, j, col, cp);
                if (curr != 0) nonzero = j;
            }
            if ((new == curr) && (nonzero != changed)) {
                // Write to single element if they share the same value
                // and mark changed.
                setElement(mtx, i, col, 0);
                setElement(mtx, nonzero, col, (new << 1)); 
                *score += (new << 1);
                printf("%d\n", *score);
                changed = nonzero;
            } else {
                // Otherwise, set new value in farthest unoccupied element.
                setElement(mtx, i, col, 0);
                setElement(mtx, (1 + cnt), col, new);
                cnt++;
            }
        }
    }
    changed = 0;
}

void mvDown(matrix * mtx, int col, int * score) {
    int i, j, cnt, changed = 0, nonzero = 0, new = 0, curr = 0;
    int *np, *cp;
    
    np = &new;
    cp = &curr;
    
    for (i = 4, cnt = 0; i > 0; i--) {
        getElement(mtx, i, col, np);
        if (new != 0) {
            curr = 0;
            for (j = i + 1; j <= 4; j++) {
                // Check for nonzero element below row i
                if (curr != 0) break;
                getElement(mtx, j, col, cp);
                if (curr != 0) nonzero = j;
            }
            if ((new == curr) && (nonzero != changed)) {
                // Write to single element if they share the same value
                // and mark changed.
                setElement(mtx, i, col, 0);
                setElement(mtx, nonzero, col, (new << 1)); 
                *score += (new << 1);
                printf("%d\n", *score);
                changed = nonzero;
            } else {
                // Otherwise, set new value in farthest unoccupied element.
                setElement(mtx, i, col, 0);
                setElement(mtx, (4 - cnt), col, new);
                cnt++;
            }
        }
    }
    changed = 0;
}

void mvRight(matrix * mtx, int row, int * score) {
    int i, j, cnt, changed = 0, nonzero = 0, new = 0, curr = 0;
    int *np, *cp;
    
    np = &new;
    cp = &curr;
    
    for (i = 4, cnt = 0; i > 0; i--) {
        getElement(mtx, row, i, np);
        if (new != 0) {
            curr = 0;
            for (j = i + 1; j <= 4; j++) {
                // Check for nonzero element to right of column i
                // If current value is not equal to zero at beginning, 
                // break for loop. Save column number as nonzero if a
                // nonzero value is read from getElement.
                // Note: print statements left to show part of the 
                // debugging process.
                if (curr != 0) break;
                getElement(mtx, row, j, cp);
                if (curr != 0) nonzero = j;
                // printf("nonzero = %d changed = %d", nonzero, changed);
                // printf(" when i = %d, j = %d\n", i, j);
            }
            if ((new == curr) && (nonzero != changed)) {
                // If the new and curr values are equal and the element 
                // holding the current value has not already been changed 
                // in the current "move", perform a bit shift and write 
                // to a single element.
                setElement(mtx, row, i, 0);
                setElement(mtx, row, nonzero, (new << 1)); 
                *score += (new << 1);
                printf("%d\n", *score);
                changed = nonzero;
                // printf("changed = %d when i = %d\n", nonzero, i);
            } else {
                // Otherwise, set new value in farthest unoccupied element.
                setElement(mtx, row, i, 0);
                setElement(mtx, row, (4 - cnt), new);
                cnt++;
            }
        }
    }
    changed = 0;
}

void mvLeft(matrix * mtx, int row, int * score) {
    int i, j, cnt, changed = 0, nonzero = 0, new = 0, curr = 0;
    int *np, *cp;
    
    np = &new;
    cp = &curr;

    for (i = 1, cnt = 0; i <= 4; i++) {
        getElement(mtx, row, i, np);
        if (new != 0) {
            curr = 0;
            // Check for nonzero to left of i
            for (j = i - 1; j > 0; j--) {
                if (curr != 0) break;
                getElement(mtx, row, j, cp);
                if (curr != 0) nonzero = j;
            }
            // Perform bit shift and write to single element if criteria met
            if ((new == curr) && (nonzero != changed)) {
                setElement(mtx, row, i, 0);
                setElement(mtx, row, nonzero, (new << 1)); 
                *score += (new << 1);
                printf("%d\n", *score);
                changed = nonzero;
            } else {
                // Set new value in farthest unoccupied element
                setElement(mtx, row, i, 0);
                setElement(mtx, row, (1 + cnt), new);
                cnt++;
            }
        }
    }
    changed = 0;
}

void spawn(matrix * mtx) {
    int i, j, r, v, cnt = 0, e = 0;
    int ii[16], jj[16];
    int * ep;

    ep = &e;
    
    // Iterate through the array and log every element equal to 
    // zero in the arrays
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 4; j++) {
            getElement(mtx, i, j, ep);
            if (e == 0) {
                ii[cnt] = i;
                jj[cnt] = j;
                cnt++;
            }
        }
    }
    
    // Generate a random number to choose which matrix element
    // will be spawned with either a 2 or 4
    r = rand() % cnt;
    v = r % 4;
    if (v == 0) v = 4;
    else v = 2;
    setElement(mtx, ii[r], jj[r], v);
}

void printMsg() {
    printf("\nThe object of the game is to join the numbers together to\n");
    printf("create a 2048 tile!\n\n");
    printf("To move left, right, up and down press j, l, i and k + ENTER.\n");
    printf("To exit the game, press q + ENTER or CTRL + C or D\n\n");
}

int main(void) {
    int i, ret, score = 0;
    int * sp;
    char ch;
    
    matrix * mtx;
    sp = &score;

    printMsg();
    
    mtx = newMatrix(4,4);
    spawn(mtx);
    printMatrix(mtx);

    // Read user input from stdin and follow each turn by spawning a
    // new tile and printing the matrix and score
    while ((ret = scanf(" %c", &ch)) != EOF) {
        if (!ret) 
            printf("Read a non-character. Input undefined.\n");
        if (ch == 'i') {
            for (i = 1; i <= 4; i++) 
                mvUp(mtx, i, sp);
        }
        if (ch == 'k') {
            for (i = 1; i <= 4; i++) 
                mvDown(mtx, i, sp);
        }
        if (ch == 'j') {
            for (i = 1; i <= 4; i++) 
                mvLeft(mtx, i, sp);
        }
        if (ch == 'l') {
            for (i = 1; i <= 4; i++) 
                mvRight(mtx, i, sp);
        }
        spawn(mtx);
        printMatrix(mtx);
        printf("Current Score: %d\n", score);
        
        if (ch == 'q') {
            deleteMatrix(mtx);
            return 0;
        }
    }

    return 0;
}
