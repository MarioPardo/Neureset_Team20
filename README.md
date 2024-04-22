# Neureset - Team 20

This is our submission for the COMP3004's final project, Neureset.

## Team Members

- Mario Pardo
- Jai Morjaria
- Anh-Tu Vothang
- Dante Farinon-Spezzano

[Video Showcase](https://drive.google.com/file/d/1LxDx1NxzFLJNb3I9p0S4b1e0asWsXC0p/view?usp=drive_link)

## Run Instructions

- Double-click the .pro file to open Qt Creator, which will automatically select a kit for you to run the project with.
- Press "configure project"
- Hit ctrl+R (command+R for Mac) or the green triangle in the bottom left corner

## Individual Contributions

**Dante**:
- Designed GUIs for SessionLogWindow and PC interfaces
- Implemented functionality for user input handling and window navigation
- Ensured smooth information flow between ActiveSessionWindow, SessionLogWindow, and PC window
- Contributed to drafting sequence diagrams (rough versions)
- Created and filled out majority of traceability matrix

**Anh-Tu**:
- Wrote up use cases
- Made sequence diagrams
- Made the class diagram
- Implemented date and time setting UI + functionality
- Contributed to traceability matrix

**Mario**:
- Set up and managed GitHub repository and project
- Created, Delegated tickets as scrum master
- Implemented session window including the logic required for stating starting, pausing, stopping, and sensor connection/disconenction including logic, and the UI
- Implemented device battery system including fully drained battery safety scenario
- Implemented permanent storage for session information and populating the PC UI
- Helped implement treatment, especially concurrency behavior between rounds
- General project planning and  decision making,  and ensured smooth work coordination

**Jai**:
- Implemented sensor voltage data generation
- Spearheaded waveform generation, including data and plotting
- Wrote dominant frequency and baseline frequency calculation algorithms
- Implemented treatment from start to finish including initial baseline measurement, dominant frequency regeneration during rounds, final measurement of baselines and wave generation/regeneration
- Added null and duplicate checks to session log window to handle erroneous user input
- Attended several lectures to ask questions and receive clarification on project direction, specifics, and edge cases. Disseminated information effectively.
- Created multiple communication channels through social media (Instagram, Discord)
- Delegated and followed up on various tasks



## Project organization

/Documentation/ - Folder for UML sequence, class, and state diagrams, traceability matrix and use cases

Neureset_Team20.pro - Project build file required by qt

*.h - C++ header files for class definitions

*.cpp - C++ source files for class implemenatations

*.ui - QT UI files
