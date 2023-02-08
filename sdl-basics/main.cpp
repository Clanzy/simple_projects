#include "app.hpp"

int main(int argc, char *args[])
{
	App app;
	app.OnInit();
	return app.OnExecute();
}
