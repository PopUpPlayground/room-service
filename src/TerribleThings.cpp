// This file does terrible things.
//
// No, really. It's not scary in-game stuff. It's awful, awful tricks I've had to
// get things to compile.
//
// If you're reading this, I'm so sorry. :(

// The libc_s.a(lib_a-ignalr.o) code wants kill and getpid, but of course those don't
// exist on our little chips... So we'll just pretend they do. ;( ;(
extern "C" {
    int _kill(int pid, int sig) { return -1; }
    int _getpid() { return -1; }
}
