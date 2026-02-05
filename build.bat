@echo off
if not exist build mkdir build
if not exist build\obj mkdir build\obj

cl /c /Fo:build\obj\ main.c vector.c file.c manager.c
cl /Fe:build\citadel.exe build\obj\main.obj build\obj\vector.obj build\obj\file.obj build\obj\manager.obj
