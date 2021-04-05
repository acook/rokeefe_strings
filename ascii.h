/* File : strings.d/ascii.h
Author : Richard A. O'Keefe
Updated: 28 April 1984
Purpose: Define Ascii mnemonics.

This file defines the ASCII control characters. Note that these
names refer to their use in communication; it is an ERROR to use
these names to talk about keyboard commands. For example, DO NOT
use EOT when you mean "end of file", as many people prefer ^Z (if
the Ascii code were taken seriously, EOT would log you off and
hang up the line as well). Similarly, DO NOT use DEL when you
mean "interrupt", many people prefer ^C. When writing a screen
editor, you should speak of tocntrl('C') rather than ETX (see the
header file "ctypes.h").
*/

#define NUL '\000' /* null character */
#define SOH '\001' /* Start Of Heading, start of message */
#define STX '\002' /* Start Of Text, end of address */
#define ETX '\003' /* End of TeXt, end of message */
#define EOT '\004' /* End Of Transmission */
#define ENQ '\005' /* ENQuiry "who are you" */
#define ACK '\006' /* (positive) ACKnowledge */
#define BEL '\007' /* ring the BELl */
#define BS '\010' /* BackSpace */
#define HT '\011' /* Horizontal Tab */
#define TAB '\011' /* an unofficial name for HT */
#define LF '\012' /* Line Feed (does not imply cr) */
#define NL '\012' /* unix unofficial name for LF: new line */
#define VT '\013' /* Vertical Tab */
#define FF '\014' /* Form Feed (new page starts AFTER this) */
#define CR '\015' /* Carriage Return */
#define SO '\016' /* Shift Out; select alternate character set */
#define SI '\017' /* Shift In; select ASCII again */
#define DLE '\020' /* Data Link Escape */
#define DC1 '\021' /* Device Control 1 */
#define XON '\021' /* transmitter on, resume output */
#define DC2 '\022' /* Device Control 2 (auxiliary on) */
#define DC3 '\023' /* Device Control 3 */
#define XOFF '\023' /* transmitter off, suspend output */
#define DC4 '\024' /* Device Control 4 (auxiliary off) */
#define NAK '\025' /* Negative AcKnowledge (signal error) */
#define SYN '\026' /* SYNchronous idle */
#define ETB '\027' /* End of Transmission Block, logical end of medium */
#define CAN '\030' /* CANcel */
#define EM '\031' /* End of Medium */
#define SUB '\032' /* SUBstitute */
#define ESC '\033' /* ESCape */
#define FS '\034' /* File Separator */
#define GS '\035' /* Group Separator */
#define RS '\036' /* Record Separator */
#define US '\037' /* Unit Separator */
#define SP '\040' /* SPace */
#define DEL '\177' /* DELete, rubout */

