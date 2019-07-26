# Debug Flow
Debug flow is a debug manager.

This project is currently in development.

Debug flow will make debugging with console logs more easyer and more flexible.
The most development environments have a simple console with almost no options, even changing the log level on the go is usually not possible.

Debug flow is seperate from a development environments, it support all kinds of input sources, much different filters can be applied and there are different ways to show the output. The goal is the let developers build a convient debugging envirmoment within a few minutes that saves hours.

A few examples:
- input from executable
- input from serial ports
- input from sockets
- read from file
- filtering on log level
- filtering on tag
- hidding log context
- adding colors to specific text
- splitting to diffent windows
- saving to file
- show data in console
- show html context
- console with realtime filtering
- console with collapsable tree debugging
- showing a measurement on a widget
- showing measurements in a graph
- showing measurements in a table
- synchronizing all windows with a timeline
- outputs to communicate back

And so on, to make that possible in a user interface the application works with flow programming, where each of that functions is a node. The goal to make it possible to change the flow realtime with backwards updates.

