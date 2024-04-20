## 3004 Team 20 Design Decisions

### Treatment:

- The device treatment system implements a **pseudo-observer pattern** - the device being the central hub, and all the sensors subscribe to it to tell them when and what to do.
- It is a pseudo-pattern since it does not use signals and slots, but rather uses futures and for loops to achieve concurrency.
- The “engine” of the device and treatment is a QTimer which calls a “run” function every x (in this case 1.5) seconds. The run function determines what the device should do based on its current state and its member variables.
- Therefore, the device implements the **State** pattern.
- The QTimer is non-blocking in nature, which is why we decided to use it. This way, the program can be interrupted in the middle of treatment by signals such as pause, stop, disconnect, etc.
- The ActiveSessionWindow class sends signals to Device about stopping, pausing, disconnected sensors, etc., so Device is an **observer** of ActiveSessionWindow


### Battery:

- The battery system implements the Singleton and Observer design patterns. 
- **Singleton**: One single instance of the battery manager system is used by the entire system - a reference to it gets passed to any component that needs to know about the system’s battery.
- **Observer**: The mentioned single instance of the battery manager acts as a central hub for the battery system, it broadcasts signals which then the components who need this information, subscribe to these signals to update their respective battery components

### Session Log/ PC UI:

- The Session Log draws information from the MainMenu class, which the Device saves to when it’s done.
- SessionLog iterates over the MainMenu’s sessions vector to pull information from it and then uses a QListView to display session dates and times.
- This ListView allows users to select individual sessions and send them to the PC UI, writing them to a file in the build folder named session-log.json.
- The PC UI reads in data from the json file, parsing a date and time, first baseline, and second baseline. It then displays this data in a QListView.
	
### Date & Time:
- The date and time window uses a QDateTimePicker to allow users to select a date.
- This then emits a signal to the MainMenu class’ handleDateTimeChanged() slot which sets the MainMenu’s internal date and time, which the MainMenu uses when creating session objects.
- MainMenu is therefore an observer of the date and time window.

### MainMenu:
- The main menu controls where what windows the user can access, and is a mediator for the entire program.
- Other components can access important information, like the DateTime, or the sessions performed in this run of the program, through the Main Menu.
