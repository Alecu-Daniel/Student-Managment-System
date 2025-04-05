Student Management System

A lightweight, user-friendly desktop application for managing tabular data related to students or any structured information, built using wxWidgets.

Features
- Customizable Grid: Add/remove rows and columns with ease.
- Column Label Editing: Double-click to rename columns.
- Data Persistence: Save and load table data to/from `.txt` files.
- Help Section: Built-in FAQ with guidance for common actions.


Data is stored in a human-readable `.txt` format:
- First line: row and column count
- Column labels (one per line)
- Cell values + coordinates (row, col)

Spaces are safely handled via underscores during save/load.

| Action                     | How to perform it                                 |
|----------------------------|---------------------------------------------------|
| Save Table                 | Click Save and choose a destination               |
| Load Table                 | Click Load and select a file                      |
| Add Row(s)                 | Click Add Row (input a number for multiple rows)  |
| Add Column                 | Click Add Column and label the new column         |
| Delete Row/Column          | Select it and press Delete                        |
| Rename Column              | Double-click the column header                    |
| Get Help                   | Click Help to open the FAQ section                |
