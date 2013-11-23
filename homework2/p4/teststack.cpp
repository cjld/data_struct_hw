void fuck(int x) {
    if (x<0) return;
    fuck(x-1);
}

int main() {
    fuck(1000000);
}