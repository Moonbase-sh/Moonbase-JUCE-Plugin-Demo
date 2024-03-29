# Moonbase Plugin Demo

## Introduction
This repository demonstrates implementation of the `moonbase_JUCEClient` module into a JUCE audio plugin. The module is a plug and play JUCE module for easy licensing integration within the Moonbase environment. 
<br>[For more information on the module, click here.](https://github.com/Moonbase-sh/moonbase_JUCEClient)
<br>

## Cloning the project
This example project includes its dependencies ([JUCE](https://github.com/juce-framework/JUCE) and the [moonbase_JUCEClient](https://github.com/Moonbase-sh/moonbase_JUCEClient) custom JUCE module) as [submodules](https://github.com/Moonbase-sh/Moonbase-JUCE-App-Demo/tree/main/Submodules). In order for the project to be able build correctly, please clone recursing the submodules: 

```bash
$ git clone https://github.com/Moonbase-sh/Moonbase-JUCE-Plugin-Demo --recurse-submodules
```
**or** initialise the submodules after cloning:

```bash
$ git clone
$ git submodule update --init --recursive
```

## Building the project
The example project can either be built using the Projucer and exporting the macOS/Windows platform specific projects for Xcode/Visual Studio 
<br>
**or** 
<br>alternatively the repository is setup for usage with VSCode and the 'Task Runner' extension. You can find several relevant build scripts under [/Scripts](https://github.com/Moonbase-sh/Moonbase-JUCE-App-Demo/tree/main/Scripts). (The VSCode setup still depends on XCode/Visual Studio 2022 being installed for their compilers and build tools).


## The Submodule
The [moonbase_JUCEClient](https://github.com/Moonbase-sh/moonbase_JUCEClient) submodule is a custom JUCE module. It can be added to your JUCE project, as you would add any other JUCE modules. See the [Moonbase Plugin Demo.jucer](https://github.com/Moonbase-sh/Moonbase-JUCE-Plugin-Demo/blob/main/Moonbase%20Plugin%20Demo.jucer) file. 

To easily open and view the .jucer project file using the appropriate version of JUCE, you can use the included `OpenJucerProject.sh` bash script located at [/Scripts/OpenJucerProject.sh](https://github.com/Moonbase-sh/Moonbase-JUCE-App-Demo/blob/main/Scripts/OpenJucerProject.sh). The script will first build Projucer from the Submodules directory and then use the build to load the .jucer project file.

Looking at the `Modules` section in the .jucer project, you'll find the `moonbase_JUCEClient` module added to the project.
![Projucer Module Image](/Assets/Readme/module.png "Projucer Module Image")
<br>

## The Config File
Located in the [/Resources](/Resources) directory, the [moonbase_api_config.json](/Resources/moonbase_api_config.json) file is a configuration file that is required by the `moonbase_JUCEClient` module. It contains the necessary information for the module to communicate with the Moonbase API.
<br> 
When added to the .jucer project, the file is compiled as a `Binary Resource`. This is the default setting; when added like this, the Moonbase API will automatically find the resource and use it to configure the module.
![Projucer Config Image](/Assets/Readme/config.png "Projucer Config Image")
<br>
The config file for your project can be generated per product in your Moonbase admin app, as part of the implementation guide for licensing of the product.
<br>
A Moonbase config file is a json formatted document, looking like this: 
```json
{
    "productId" : "juce-app-demo",
    "licenseFileLocation" : "Moonbase/JUCE App Demo/license.mb",
    "baseUrl" : "https://demo.moonbase.sh",
    "offlineUrl" : "https://demo.moonbase.sh/activate",
    "publicKey" : "YnFtM4FhAzk80Ehm....."
}
```

**`productId`**
The unique identifier for your product. This is the product ID you set when creating a product in the Moonbase admin app.

**`licenseFileLocation`**
The location of the license file relative to the user application data directory (base directory). This is the location where the module will install the license file.

macOS base directory: `~/Library (/Users/<username>/Library)` (potentially hidden)
<br>
Windows base directory: `C:\Users\<username>\AppData\Roaming`

**`baseUrl`**
The base URL of the Moonbase API. This is the URL the module will use to communicate with the Moonbase API. As Moonbase vendor you'll receive your own subdomain. 

**`offlineUrl`**
The URL the user interface will show, where a user can generate an offline activation file from an activation request file generated through the Moonbase API.

**`publicKey`**
The public key of the Moonbase API. This key is used to verify the authenticity of the license file.
<br>
## Code Implementation
### Structure
The `moonbase_JUCEClient` module is structured into two logical parts, following the Processor/Editor pattern common in JUCE projects: 

**The [Moonbase::JUCEClient::API class](https://github.com/Moonbase-sh/moonbase_JUCEClient/blob/main/Source/JUCEClientAPI.h)**
is responsible for the communication with the Moonbase API and should be kept alive during the entire lifetime of your executable. Amongst others, it provides functions to activate, deactivate, and check the license status of the product. The API class does the heavy lifting for you, so you don't need to worry about license checks and activation logic in your application code. It will take care of all backend logic and provide you with the necessary information about the activation status of your product.

**The [Moonbase::JUCEClient::ActivationUI class](https://github.com/Moonbase-sh/moonbase_JUCEClient/blob/main/Source/JUCEClientUI.h)**
is an optional JUCE UI. It provides a simple user interface to activate and deactivate the product. You're free to use only the API and provide your own user interface, or can use the API + the UI. While the ActivationUI class provides a few basic look setters for things like the company or spinner icons, we recommend forking the module, if you want to gain greater control and customisation over the UI or just write your own, using only the API class and calling its relevant member functions yourself.
<br>
### Macros
The `moonbase_JUCEClient` module provides a set of handy Macros in [/Source/Macros.h](https://github.com/Moonbase-sh/moonbase_JUCEClient/blob/main/Source/Macros.h).
<br>
These macros simplify the integration of the module into various types of juce projects, without worrying about integration details. This example project makes use of these Macros, in order to implement Moonbase into the project with only a few lines of code. 

For most usecases it's enough to specify in the processor/persistent part of your code object to initialize an Moonbase API object:
```cpp
MOONBASE_DECLARE_LICENSING_USING_JUCE_PROJECTINFO
```
<br>


See [/Submodules/moonbase_JUCEClient/Source/Macros.h](https://github.com/Moonbase-sh/moonbase_JUCEClient/blob/main/Source/Macros.h) for more info and an overview of all available Macros (requires you to first add the moonbase_api_config.json config file to your JUCE BinaryData as described above). 

#### Note:
Make sure that you have your `Company Name` field set in your Projucer project and make sure it fits whatever is registered with Moonbase - license checks will fail, if the company name of your JUCE project doesn't match the company name registered with Moonbase for a specific configuration file.
![Company Name Projucer Setting](/Assets/Readme/companyname.png)
<br>

## The Plugin Example
This example project was created going from a `JUCE Audio Plugin` boilerplate project. 

See the [PluginProcessor.h](https://github.com/Moonbase-sh/Moonbase-JUCE-Plugin-Demo/blob/main/Source/PluginProcessor.h) and [PluginProcessor.cpp](https://github.com/Moonbase-sh/Moonbase-JUCE-Plugin-Demo/blob/main/Source/PluginProcessor.cpp) files for the implementation of the Moonbase API object in the processor part of the plugin.

See the [PluginEditor.h](https://github.com/Moonbase-sh/Moonbase-JUCE-Plugin-Demo/blob/main/Source/PluginEditor.h) and [PluginEditor.cpp](https://github.com/Moonbase-sh/Moonbase-JUCE-Plugin-Demo/blob/main/Source/PluginEditor.cpp) files for the implementation of the Moonbase ActivationUI object in the editor part of the plugin.
<br>

