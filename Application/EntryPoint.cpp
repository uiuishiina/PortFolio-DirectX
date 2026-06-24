#include"Application.h"

int main() {

	Application App;

	if (!App.initialize_App()) {
		return -1;
	}
	App.run_App();

	return 0;
}