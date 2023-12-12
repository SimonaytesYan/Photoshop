#include <dlfcn.h>

#include "GetPlugins.h"

typedef plugin::Plugin* (*GetInstanceType)(plugin::App *app);

plugin::Plugin* LoadPlugin(const char* path, plugin::App* app)
{
	void* dll_hand = dlopen(path, RTLD_NOW | RTLD_LOCAL);

	if (dlerror() != nullptr)
	{
		fprintf(stderr, "dlerr    = <%s>\n", dlerror());
		fprintf(stderr, "dll_hand = %d\n",   dll_hand);
		return nullptr;
	}

	GetInstanceType get_plugin = (GetInstanceType)dlsym(dll_hand, "getInstance");
	
	if (dlerror() != nullptr)
	{
		fprintf(stderr, "dlerr 		 = <%s>\n", dlerror());
		fprintf(stderr, "GetInstance = %p\n",   get_plugin);
		return nullptr;
	}

	plugin::Plugin* my_plugin = get_plugin(app);

	return my_plugin;
}

DynArray<char*> GetPluginNames()
{
	FILE* file = fopen("Plugins/Plugins", "r");

	DynArray<char*> plugin_names;
	
	char* name = new char[100];
	strcpy(name, "Plugins/");

	while (NULL != fgets(name + 8, 100, file))
	{
		plugin_names.PushBack(name);
		if (name[strlen(name) - 1] == '\n') 
			name[strlen(name) - 1] = 0;

		fprintf(stderr, "name = %s\n", name);
		name = new char[100];
		strcpy(name, "Plugins/");
	}

	delete[] name;

	return plugin_names;
}

plugin::Plugin* LoadPlugins(plugin::App* app, Gui* root)
{
	DynArray<char*> plugin_names = GetPluginNames();

	for (int i = 0; i < plugin_names.GetLength(); i++)
	{
        plugin::Plugin* new_plugin = LoadPlugin(plugin_names[i], app);

        if (new_plugin == nullptr)
		{
			fprintf(stderr, "Error during loading plugin [%d] <%s> \n", i, plugin_names[i]);
		}
        else
        {
            if (new_plugin->name == nullptr)
				new_plugin->name = "(null)";
                
		    root->AddPlugin(new_plugin);
        }
	}
}