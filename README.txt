####### Midi Editor v 0.1 #########

Midi Editor is an open source tool for modifying MIDI files.

FEATURES:

	Four main functions:

		1) Strummify
		   Apply to a guitar track to separate guitar chords, creating a more full
		   and natural sound. Auto-determines upstroke or downstroke for each chord.
		   
		2) Change Delta
			Apply to any track to change note placement. Use a small  magnitude
			randomize to make a track sound slightly less like a computer.
			
		3) Change Note
			Apply to any note to change that note value. The magnitude slider is the
			new note, and the note drop down is the old note.
			
		4) Change Volume
			Apply to any track to change the volume.
		
	Parameters:
		These functions can all be applied to any subset of a track, further filtered by
		a set of measures or a specific note. Many functions allow the use of the randomize
		feature.
		
	General Usage: 
		Select a file. Select a function. Select parameters. Press
		apply changes. Press play output to hear the change. If you like the change,
		press keep changes. The updated file will be saved in the same directory as the
		original file. It will not overwrite the original file.
		
	Notes: 
		Enter the correct time signature in order for measure select functionality
		to work properly.
	
Bugs: 
	1) The change delta function currently does not keep chords together. Applying a randomize
	change delta to a file with chords will cause the chord notes to no longer
	be together. This may or may not be desirable.
	
	*2) On very rare occasions, change delta or strummify may produce corrupted output,
	due to a failure to correctly order the newly changed notes. Re-apply changes
	and test output again to be sure the file is now ok. If repeated corrupted
	outputs are produced, reduce the parameter range of your desired changes.
	
Build Instructions:

	I have only successfully built this on linux.
	
	Dependencies:
		QT creator https://www.qt.io/ide/
		MidiFile https://github.com/craigsapp/midifile
		
		
	Linux:
		1) Import the project files into QT creator
		2) Download midifile (link above) and build midifile.a using command "make library"
		3) In QTCreator, right click on project name in file tree, and click add library.
		   Select add external library. Navigate to midifile.a and select it. 
		4) Build and run
		
	Hypothetical Windows Build: (This hasn't worked for me, but it is supposed to)
		-Open MidiFile in Visual Studio and build a static library (.lib)
		-Import MidiEditor project to QT creator
		-in MIDIEditor.pro remove everything after the line that starts with FORMS
		-Right click the project name and add directory
			-Add the MifiFile.lib to your project
		-Project should run now. (Though it does not work for me).
		
		#Current non-working configuration (from .pro):
			INCLUDEPATH += $$PWD/../midifile-master/include
			LIBS += -L$$PWD/../midifile-master/visual-studio/DebugLib/ -lmidifile
			
			Produces LNK2019 and LNK2001 Errors for all midifile library functions
		
		
		
		
			
		
	
	
	
	
