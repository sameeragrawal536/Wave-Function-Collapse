#include <iostream>
#include <algorithm>
#include <random>
#include "../include/WFC.h"
#include "../include/PPM.h"

// Hey, pal. Looks like you just collapsed your last wave function *pulls out a coconut gun*

void WFC::wfc()
{
	// Define grid position
	int x = 0, y = 0;

	// Start with the first Element in the output
	observe(output[y][x].wave);

}

// Generate adjacency rules from input img
HashTable* WFC::ruleGeneration(PPMImage img) {
    HashTable rules[4];

    // Define array to store all 3x3 tiles in image
    Pattern patterns[(img.x-2)*(img.y-2)];
    int len = (img.x-2)*(img.y-2);

    for (int i = 0; i < img.y-3; i++) {
        for (int j = 0; j < img.x-3; j++) {
            Pattern* pattern = new Pattern();
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    pattern->pixels.writePixel(l,k,img.pixelAt(j+l,i+k));
                }
            }
            patterns[i*(img.x-2)+j] = *pattern;
        }
    }

    // Find number of unique patterns
    int cnt = 0;
    bool found = false;
    for (int i = 0; i < len; i++) {
        found = false;
        for (int j = 0; j < i; j++) {
            if (patterns[j].pixels == patterns[i].pixels) {
                found = true;
            }
        }
        if (!(found)) {
            cnt++;
        }
    }
    
    // Define hash table for top, left, right, and bottom patterns
    HashTable* topRules = new HashTable(cnt);
    HashTable* leftRules = new HashTable(cnt);
    HashTable* rightRules = new HashTable(cnt);
    HashTable* bottomRules = new HashTable(cnt);

    // Insert each unique pattern in input image as a key into each hash table
    for (int i = 0; i < len; i++) {
        if (!(topRules->contains(patterns[i]))) {
            topRules->insert(patterns[i]);
        }
        if (!(leftRules->contains(patterns[i]))) {
            leftRules->insert(patterns[i]);
        }
        if (!(rightRules->contains(patterns[i]))) {
            rightRules->insert(patterns[i]);
        }
        if (!(bottomRules->contains(patterns[i]))) {
            bottomRules->insert(patterns[i]);
        }
    }

    // Add adjacent patterns
    for (int i = 0; i < topRules->getLength(); i++) {
        for (int j = 0; j < len; j++) {
            if (patterns[j].pixels == topRules->get(i).head->pat.pixels) {
                if (j > img.x) { // If we're on the second row or below, we can have a pattern above
                    if (!(topRules->get(i).contains(patterns[j-img.x]))) { // If the adjacent pattern above isn't already in the rules
                        topRules->insert(patterns[j-img.x]);
                    }
                }
                if ((j%img.x) > 0) { // If we're at least one tile along a row, we can have a pattern to the left
                    if (!(leftRules->get(i).contains(patterns[j-1]))) { // If the adjacent pattern to the left isn't already in the rules
                        leftRules->insert(patterns[j-1]);
                    }
                }
                if ((j%(img.x-1)) > 0) { // If we're at least one tile before the end of a row, we can have a pattern to the right
                    if (!(rightRules->get(i).contains(patterns[j+1]))) { // If the adjacent pattern to the right isn't already in the rules
                        rightRules->insert(patterns[j+1]); 
                    }
                }
                if (j < (len-img.x)) { // If we're at least one row before the end, we can have a pattern below
                    if (!(bottomRules->get(i).contains(patterns[j+img.x]))) { // If the adjacent pattern below isn't already in the rules
                        bottomRules->insert(patterns[j+img.x]);
                    }
                }
            }
        }
    }

    rules[0] = *topRules;
    rules[1] = *leftRules;
    rules[2] = *rightRules;
    rules[3] = *bottomRules;

    return rules;
}

void WFC::observe(Wave* wave)
{
	// since every Pattern is weighted, we'll use a vector to hold all possible Patterns in the distribution.
	// Weight is implemented via duplicates in the vector
	vector<Pattern> distribution;
	for (int i = 0; i < wave->domain.size(); i++)
	{
		for (int j = 0; j < pattern.weight; j++) distribution.push_back(pattern);
	}
	// Shuffle the distribution
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(cards_), std::end(cards_), rng);
	// ...and pick a Pattern.
	int randomIndex = rand() % SP.size();
}

int main(){
    PPMImage *image = new PPMImage();
    image->readPPM("/Users/sameeragrawal/Desktop/hello.ppm");

    std::cout << image->y << " x " << image->x << "\n";

    std::cout << *image << "\n";
}