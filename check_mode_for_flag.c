#include <gbpSID.h>

int check_mode_for_flag(int mode, int flag) {
    return ((mode & flag) == flag);
}
