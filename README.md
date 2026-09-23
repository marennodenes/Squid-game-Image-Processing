# Squid Game - Image Processing

An application that generates a Squid Game image using composition operations, with three images as input. 

## How it works
|Step|Operation|Result|
|----|---------|------|
|1|'squid_head' **+** 'squid_body'|The shapes are merged. Where they overlap, the pixels get a new color|
|2|result **−** 'squid_points'|The circles are cut out as holes|

## Requirements
- Windows with Visual Studio 2022
- Worklod **Desktop development with C++**
- Component **C++ MFC and ATL for latest build tools (x86 & x64, v. 143)**, installed through the Visual Studio Installer. 

## Build and run
1. Open the '.sln' file in the 'SRC' folder.
2. Select **Build → Build Solution**
3. Select **Debug**.

## Usage
1. Choose **File → Open** and open 'squid_head.png', 'squid_body.png' and 'squid_points.png' from the images folder.
2. In the 'squid_head' window, choose **ImageProcessing → Composite**. Select operator **+** and second image 'squid_body'.
3. In the same window, choose **Composite** again. Select operator **−** and second image s'quid_points'.

## Project structure
```
SRC/        Visual Studio project
images/     Input images and the result image
cximage/    CxImage library: headers, prebuilt libraries and sources 
```

## Troubleshooting
1. Open 'cmimage/CxImgLib.sln'.
2. Select **Unicode Debug** and **Win32**.
3. Choose **Build → Build Solution**.
4. Rebuild the project in 'SRC'.
