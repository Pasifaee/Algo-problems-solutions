#include <iostream>

void change_colour(char highway[], int highway_white[], int* white, char colour, int start, int ending, int x, int x_l, int x_r, int pow2) {
    if (highway[x] == 'B' || highway[x] == 'C') {
        if (x_l < x_r) {
            highway[x * 2] = highway[x];
            highway[x * 2 + 1] = highway[x];
            if (highway[x] == 'B') {
                highway_white[x * 2] = (x_r - x_l + 1) / 2;
                highway_white[x * 2 + 1] = (x_r - x_l + 1) / 2;
            }
            else {
                highway_white[x * 2] = 0;
                highway_white[x * 2 + 1] = 0;
            }
        }
    }

    if (colour == highway[x]) {
        if (colour == 'B') {
            *white += x_r - x_l + 1;
            highway_white[x] = x_r - x_l + 1;
        }
        else {
            highway_white[x] = 0;
        }
        return;
    }
    else {
        highway[x] = 'M';
    }

    if (start == x_l && ending == x_r) {
        highway[x] = colour;
        if (colour == 'B') {
            *white += x_r - x_l + 1;
            highway_white[x] = x_r - x_l + 1;
        }
        else {
            highway_white[x] = 0;
        }
        return;
    }

    int x_mid = (x_l + x_r) / 2;
    if (ending <= x_mid) { // do lewego syna
        change_colour(highway, highway_white, white, colour, start, ending, 2 * x, x_l, x_mid, pow2);
    }
    else if (start > x_mid) { // do prawego syna
        change_colour(highway, highway_white, white, colour, start, ending, 2 * x + 1, x_mid + 1, x_r, pow2);
    }
    else { // do obu synów
        change_colour(highway, highway_white, white, colour, start, x_mid, 2 * x, x_l, x_mid, pow2);
        change_colour(highway, highway_white, white, colour, x_mid + 1, ending, 2 * x + 1, x_mid + 1, x_r, pow2);
    }

    if (2 * x < pow2 * 2) {
        highway_white[x] = highway_white[2 * x] + highway_white[2 * x + 1];
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    // Tworzenie drzewa przedziałowego.
    int pow2 = 1;
    while (pow2 < n) {
        pow2 *= 2;
    }
    char highway[2 * pow2 + 1]; // drzewo przedziałowe z kolorami
    int highway_white[2 * pow2 + 1]; // drzewo przedziałowe z liczbą białych fragmentów
    highway[1] = 'C'; // black
    for (int i = 1; i <= 2 * pow2; i++) {
        highway_white[i] = 0;
    }
    int start, ending;
    char colour; // white = B, black = C, mixed = M
    for (int i = 0; i < m; i++) {
        std::cin >> start >> ending >> colour;
        int white = 0;
        change_colour(highway, highway_white, &white, colour, start, ending, 1, 1, pow2, pow2);
        std::cout << highway_white[1] << "\n";
    }
}
