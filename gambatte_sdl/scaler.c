
#include "scaler.h"


/* Upscale from 160x144 to 320x240 */
void gb_upscale(uint32_t *to, uint32_t *from) {
    uint32_t reg1, reg2, reg3, reg4;
    unsigned int x,y;

    /* Little explanation:
     * we transform three lines of pixels into five lines.
     * Each line has twice the number of pixels.
     * So each turn, we read two pixels (2 * 16-bit pixel) from the upper line,
     * two from the middle line, and two from the bottom line.
     * Each pixel from those lines will be doubled and added to the first, third or fifth
     * line on the output.
     * The pixels composing lines two and four will be calculated as the average between
     * the pixels above them and the pixels under them.
     * Easy isn't it?
     */

    for (y=0; y < 240/5; y++) {
        for(x=0; x < 320/4; x++) {
            __builtin_prefetch(to+4, 1);

            reg2 = *from;

            // first pixel, upper line => reg1
            reg1 = reg2 & 0xffff0000;
            reg1 |= reg1 >> 16;
            *(to+1) = reg1;
            reg1 = (reg1 & 0xf7def7de) >> 1;

            // second pixel, upper line => reg2
            reg2 = reg2 & 0xffff;
            reg2 |= reg2 << 16;
            *to = reg2;
            reg2 = (reg2 & 0xf7def7de) >> 1;

            reg4 = *(from + 160/2);

            // first pixel, middle line => reg3
            reg3 = reg4 & 0xffff0000;
            reg3 |= reg3 >> 16;
            *(to + 2*320/2 +1) = reg3;
            reg3 = (reg3 & 0xf7def7de) >> 1;

            // second pixel, middle line => reg4
            reg4 = reg4 & 0xffff;
            reg4 |= reg4 << 16;
            *(to + 2*320/2) = reg4;
            reg4 = (reg4 & 0xf7def7de) >> 1;

            // We calculate the first pixel of the 2nd output line.
            *(to + 320/2 +1) = reg1 + reg3;

            // We calculate the second pixel of the 2nd output line.
            *(to + 320/2) = reg2 + reg4;

            reg2 = *(from++ + 2*160/2);

            // first pixel, bottom line => reg1
            reg1 = reg2 & 0xffff0000;
            reg1 |= reg1 >> 16;
            *(to + 4*320/2 +1) = reg1;
            reg1 = (reg1 & 0xf7def7de) >> 1;

            // second pixel, bottom line => reg2
            reg2 = reg2 & 0xffff;
            reg2 |= reg2 << 16;
            *(to + 4*320/2) = reg2;
            reg2 = (reg2 & 0xf7def7de) >> 1;

            // We calculate the two pixels of the 4th line.
            *(to++ + 3*320/2) = reg2 + reg4;
            *(to++ + 3*320/2) = reg1 + reg3;
        }
        to += 4*320/2;
        from += 2*160/2;
    }
}
