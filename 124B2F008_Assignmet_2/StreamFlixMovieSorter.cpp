#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For setw
using namespace std;

struct Movie {
    string title;
    double rating;
    int releaseYear;
    int watchPopularity;
};

int partition(vector<Movie>& movies, int low, int high, int criteria) {
    Movie pivot = movies[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        bool condition = false;
        if (criteria == 1) condition = movies[j].rating > pivot.rating;
        else if (criteria == 2) condition = movies[j].releaseYear > pivot.releaseYear;
        else if (criteria == 3) condition = movies[j].watchPopularity > pivot.watchPopularity;

        if (condition) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return i + 1;
}

void quicksort(vector<Movie>& movies, int low, int high, int criteria) {
    if (low < high) {
        int pi = partition(movies, low, high, criteria);
        quicksort(movies, low, pi - 1, criteria);
        quicksort(movies, pi + 1, high, criteria);
    }
}

// Display movies properly aligned
void displayMovies(const vector<Movie>& movies) {
    cout << "\nSorted Movies:\n";
    cout << left << setw(20) << "Title" 
         << setw(10) << "Rating" 
         << setw(10) << "Year" 
         << setw(12) << "Popularity" << endl;
    cout << string(52, '-') << endl;

    for (const auto& m : movies) {
        cout << left << setw(20) << m.title
             << setw(10) << m.rating
             << setw(10) << m.releaseYear
             << setw(12) << m.watchPopularity << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of movies: ";
    cin >> n;
    cin.ignore(); // Ignore newline

    vector<Movie> movies(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter title, rating, releaseYear, watchPopularity for movie " << i + 1 << ":\n";
        getline(cin, movies[i].title);
        cin >> movies[i].rating >> movies[i].releaseYear >> movies[i].watchPopularity;
        cin.ignore(); // Ignore newline
    }

    cout << "\nChoose sorting criteria:\n1. IMDB Rating\n2. Release Year\n3. Watch Popularity\n";
    int criteria;
    cin >> criteria;

    quicksort(movies, 0, n - 1, criteria);
    displayMovies(movies);

    return 0;
}
