#include <iostream>

int* interpretation(std::string text) {
	int* num_val = new int[47];
	int counter
	
	for (int i = 0; i < 47; i++) {
//		std::cout << text[i] << ": " << int(text[i]) << "\n";
		if (int(text[i]) == -37) num_val[i] = 219;
		else if (int(text[i]) == 32) num_val[i] = 32;
	}
	
	std::cout << "\ncounter: " << counter << "\n";
	
	return num_val;
}

int main() {
	std::string text;
	
	int* arr;
	int num[5][10];
	
//	std::cout << int('A');
	
	for (int i = 0; i < 5; i++) {
		getline(std::cin, text);
		interpretation(text);
		arr = interpretation(text);
		
		
		std::cout << "{";
		for (int j = 0; j < 47; j++) {
			std::cout << arr[j];
			if (j < 46) std::cout << ",";
			std::cout << " ";
		}
		std::cout << "\b}\n\n"; 
	}
	
	return 0;
}
