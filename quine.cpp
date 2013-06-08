#include <iostream>

int main() {
     char* z="#include <iostream> int main() { ";//char* z=\"%s\"; printf%c; printf (z,z,34,34);";
     
     char* s="%s printf (%c #include <iostream> int main() { char* z=\%c%s\%c ; char* s=\%c%s\%c; printf(s,z,34,34,z,34,34,s,34);\\\",\\\"%s\\\");}";
     printf(s,z,34,34,z,34,34,s,34,"%s");
     system("PAUSE");
}
