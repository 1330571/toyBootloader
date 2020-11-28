
#include "keyboard.h"
#include "../kernel/util.h"
#include "../ports/ports.h"
#include "../kernel/type.h"
#include "../interrupts/isr.h"
#include "../libc/string.h"
#include "../kernel/sudoProc.h"

i8 get_ascii(u8 scancode);

#define BACKSPACE 0x0E
#define ENTER 0x1C
static char key_buffer[256];
int keyState = 0;
int value = -1;
const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

i8 lastcode = (i8)255;
void keyboard_callback(registers_t regs)
{
    u8 scancode = byte_in(0x60);
    i8 ascii = get_ascii(scancode);

    if (keyState == 666)
    {
        if (lastcode == (i8)255)
        {
            char letter = sc_ascii[(int)scancode];
            if (letter < '0' || letter > '9')
                return;
            lastcode = scancode;
            append(key_buffer, to_lower(letter));
            putChar(to_lower(letter), BLACK_WHITE);
        }
        else
        {
            if (lastcode == scancode)
                return; //不允许输入一样的
            if (scancode == ENTER)
            {
                value = charToInt(key_buffer);
                regs.eax = value;
                keyState = 0;
                lastcode = (u8)-1;
            }
            else
            {
                char letter = sc_ascii[(int)scancode];
                if (letter < '0' || letter > '9')
                    return;
                lastcode = scancode;
                append(key_buffer, to_lower(letter));
                putChar(to_lower(letter), BLACK_WHITE);
            }
        }
        return;
    }

    if (scancode > 57)
        return;
    if (scancode == BACKSPACE)
    {
        delete (key_buffer);
        backOneChar();
    }
    else if (scancode == ENTER)
    {
        if (keyState == 666)
        {
            value = charToInt(key_buffer);
            regs.eax = value;
            keyState = 0;
            lastcode = (u8)-1;
        }
        else
        {
            putChars("\n", 0x0f);
            terminal(key_buffer); /* kernel-controlled function */
            newStart();
        }

        key_buffer[0] = '\0';
    }
    else
    {
        char letter = sc_ascii[(int)scancode];
        append(key_buffer, to_lower(letter));
        putChar(to_lower(letter), BLACK_WHITE);
    }
    // #ifndef RELEASE
    //     if (ascii != 'X')
    //         putChar(ascii, 0x0b);
    // #endif
}
void reset()
{
    key_buffer[0] = '\0';
    lastcode = -1;
}
void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

i8 get_ascii(u8 scancode)
{
    switch (scancode)
    {
    case 0x0:
        break;
    case 0x1:
        break;
    case 0x2:
        return '1';
    case 0x3:
        return '2';
    case 0x4:
        return '3';
    case 0x5:
        return '4';
    case 0x6:
        return '5';
    default:
        return 'X';
    }
    return 'X';
}