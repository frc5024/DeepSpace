#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>

std::vector<std::string> buffer;

void Log(std::string message){
    buffer.push_back(message);
}

void vector_print(std::vector<std::string> const &input)
{
	for (auto const& i: input) {
        std::cout << i << std::endl;
    }
}

void Display(clock_t start, clock_t current){
    double duration = (double)(current - start) / CLOCKS_PER_SEC;
    std::cout << "-- " << duration << " seconds since boot --" << std::endl;
    vector_print(buffer);
    buffer.clear();
}

int main(){
    clock_t start = clock();
    while(true){
        clock_t loop = clock();
        Log("Hello");
        Log("World");

        clock_t current = clock();
        if(buffer.size() > 0){
            Display(start, current);
        }

        // usleep(20 ) ;
    }
    return 0;
}