# Projet_Vector-_Text_based_Editor
# ASCII Geometry Drawer 🎨

![C](https://img.shields.io/badge/C-11-00599C?logo=c&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

A terminal-based geometric drawing application that renders shapes in ASCII art. Create and manipulate points, lines, circles, and polygons through simple console commands.

## ✨ Features

- **Shape Creation**:
  - Points, Lines, Circles
  - Squares, Rectangles, Polygons
- **Create a drawing area where shapes are placed.**

- **Manage commands for manipulating shapes:**
  - Add a shape
  - Display the list of shapes
  - Delete a shape
  - Clean up the drawing area
  - Display help on available commands

🎮 Command Reference

Command	Example	Description

point	point 10 10	Create point at (10,10)

line	line 5 5 20 20	Draw line between points

circle	circle 15 15 5	Add circle with radius 5

plot	plot	Render all shapes

list	list	Show all shapes with IDs

delete	delete 3	Remove shape ID 3

help	help	Show command reference

🏗 Project Structure

The project is organised into several files:

- **main.c: Contains the program's main loop and manages user interaction**.

- **area.h / area.c: Defines the Area structure and the functions associated with managing the drawing area**.

- **shapes.h / shapes.c: Defines the various geometric shapes and their associated functions**.

- **commandes.h / commandes.c: Manages user commands and their execution**.
