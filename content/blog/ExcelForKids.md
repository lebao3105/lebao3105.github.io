LU: 2025-04-09 18:xx UTC+7
TI: Creating an entire Excel worksheet just for... very basic maths

#6 I'm tired with manually writing HTML for pages. Also with VBA.

#4 Introduction

Welcome to the second "blog" post.

Vsmart Camera patches are still what they are - or say, no more progress. That is because of skill issues and I have else things to do.

Now let's talk about our main topic.

My brother, who is going to his 5th grade, sucks. He loves TV, hates to study. We, including I myself, do not have any proper way to fix that.

The consequence is foreseeable: He is not able, no, can, do divisions and multiplies. But not as fast as we wanted. Seems he calculate using his read-for-times formulas and plus operators.

I rewrote <a href="https://github.com/lebao3105/app1cli">my first application</a> for him to try. Does not improve much.

At the other hand, I, uhm... love to b*lly him. For the sake of fun. And all are <bold>harmless hurts</bold>.

My dad do not like app1 as it is not graphical and misses features. Fixable, but I did not do it (and even archive the repository once again).

That is why we are here. (do NOT ask for a GUI app, <strike>I'm going to do it real quick.</strike> Never mind - he already got covered.)

#4 VBA
Yes. Although I have a build of Excel which is newer than Microsoft's requirements, no Python thing shows up.

There is a Python add-on. Unofficial and installed on my PC, but I do not want to touch Excel again.

With that, Visual Basic is the only way. That means you will have to enable macros for your sheet.

By the way some notes:
<ul>
    <li>None of us, including my dad who used VBA before, is VB/VBA professionals.</li>
    <li>Probably there are things that we can use or drop, but no time to check.</li>
    <li>This involves the use of macros. Remember how people got scared of it?</li>
    <li>We will work with <bold>Sheet1</bold> - the first sheet ever that Excel makes for new documents.</li>
</ul>

#4 Setup

There are 20 questions = 20 rows that my brother must complete.
Three first columns are used for the formula:
<ul>
    <li>The first and third are numbers. Randomized.</li>
    <li>The second one is "x", a multiply sign.</li>
</ul>

The next column is just "=". The next is the user input.

The next column is the check.

Now head to Insert -> More Controls -> Create a Microsuck Forms 2.0 CommandButton somewhere.
Double click on it, which will shows a Win32, pathetic (because of its EYES HURTING NATURE) IDE.

Three - Two - One: you're already suffering it:

<img src="ExcelForKids_Images/Screenshot 2025-04-06 184154.png" width="800"/>

To execute, exit Design Mode (Excel has a button for that somewhere, lazy to check), Press F5 while the caret is <bold>placed</bold> inside the function you want to run.

#4 Basics of Basic

<ul>
    <li><code>Dim</code> declares variables.</li>
    <li><code>Sub</code>-<code>End Sub</code> pair declares a function.</li>
    <li><code>Do While</code>-<code>Loop</code> declares a loop.</li>
    <li>Conditional statements? <code>If</code>-<code>Then</code>-<code>Else</code>-<code>End If</code>.</li>
    <li>Concatenate stuff using <code>&</code>. Yes you heard it right! You do not even need to cast an integer value to string!</li>
    <li>Wonder how the C's <code>switch</code>-<code>case</code> look like in VBA? Here you go:
        <pre>
            <span>Case Select &lt;variable&gt;</span>
            <span>    Case &lt;value&gt;</span>
            <span>        ' do stuff, also yes this is a comment</span>
            <span>    Case lowest To highest</span>
            <span>        ' do stuff</span>
            <span>    Case Else</span>
            <span>        MsgBox "What is this?"</span>
        </pre>
    </li>
</ul>

Werid ass, don't they?

#4 Random

Here is the first task we have done.

Both numbers must be randomized. After a while looking at Microsuck's API, I tried to use <code>Randomize</code> and <code>Rnd</code>.

My father used to do VBA. "Used to do". He now forgets most things, but still remember that no need for 2 functions like that.

And here comes <code>WorksheetFunction</code>. As the name suggests, it contains functions that you normally use with <code>=</code> prefix in normal Excel worksheets.

<code>RandBetween</code> is the function that we wanted. Pass 3 and 9 as the randomize ranges.

Now we need to fill in the randomized number to the cells. Declare a variable showing the current row, create a loop:

<pre>
    <span>Dim dong As Integer</span>
    <span>dong = 1</span>
    <span>Do While dong &lt; 21</span>
    <span>    Sheet1.Cells(dong, 1) = WorksheetFunction.RandBetween(3, 9)</span>
    <span>    Sheet1.Cells(dong, 3) = WorksheetFunction.RandBetween(3, 9)</span>
    <span>    dong = dong + 1</span>
    <span>Loop</span>
</pre>

Also do not forget to clear the cells:
<pre>
    <span>Range("E1", "F21").Clear</span>
</pre>

Knowing E and F, or rather the 5th and 6th columns, are user inputs and check results.

#4 Check the input

Create another CommandButton. Now we switch to its click handler.
The first thing to do is to declare variables for the current line, input and the right answer.
The right answer is always the multiply of the first and third columns. Compare with the user input, show the check result in the sixth column.
Simple as that.

#4 Scores

My dad wanted this. Not sure if this will improve my brother, but no reason to not add it.
20 questions, 5 points each. Inside the second button's click handler, declare a new variable, minus the total score by 5 if the input is not the right answer.

After calculating the score, we would like to tell the user something. Encourage them to continue improving themself.
<span>MsgBox is here to help:</span>

<pre>
    <span>Select Case diem</span>
    <span>    Case 100</span>
    <span>        MsgBox Sheet1.Cells(21, 12), vbOKOnly, "From the whole family:"</span>
    <span>    Case 80 To 99</span>
    <span>        MsgBox Sheet1.Cells(22, 12), vbOKOnly, "From the whole family:"</span>
    <span>    Case 40 To 79</span>
    <span>        MsgBox Sheet1.Cells(23, 12), vbOKOnly, "From the whole family:"</span>
    <span>    Case Else</span>
    <span>        MsgBox Sheet1.Cells(24, 12), vbOKOnly, "From the whole family:"</span>
    <span>End Select</span>
</pre>

Notice how we use different cells to store the messages. Why? Because we can't use Vietnamese characters inside the IDE somehow.
<code>diem</code> here is the score.

#4 Timer

A countdown timer is a must. It makes the "game" more interesting (with us it's not).
This is where things become more complicating.
<ul>
    <li>The first, or Start button from now, will start the timer;</li>
    <li>Also do not forget to pick a cell to show the remaining time, here I choose I12;</li>
    <li>The time initially was 2 minutes, then reduced to 1 minute for testing sake.</li>
    <li>When the timer stops is when we calculate the score.</li>
</ul>

Simple as that.
After going around the internet, I found out <code>Application.OnTime</code>. It will trigger the specified function (which is specified as a string, yes just its name. Python importlib moment lol) at a specific time.

Inside VBA, go to Insert > Module. Create a function named <code>updateTimeLabel</code>.
Using <code>ThisWorkbook.Sheets()</code> to get the sheet object, then use its <code>Range</code> to get the Cell (don't remember why Cells() did not work), we can compare, minus the remaining time and call the <code>updateTimeLabel</code> on the next second.

<pre>
    <span>Sub updateTimeLabel()</span>
    <span>    Dim wksh As Worksheet</span>
    <span>    Set wksh = ThisWorkbook.Sheets("Sheet1")</span>
    <span>    wksh.Range("I12").Locked = False</span>
    <span>    If (Not wksh.Range("I12").Value = 0) Then</span>
    <span>        wksh.Range("I12").Value = wksh.Range("I12").Value - TimeValue("00:00:01")</span>
    <span>        Application.OnTime Now() + TimeValue("00:00:01"), "updateTimeLabel"</span>
    <span>    Else</span>
    <span>        wksh.Range("E1:F21").Locked = True</span>
    <span>        wksh.Range("I12").Locked = True</span>
    <span>        wksh.Range("I12").Value = "Het gio!"</span>
    <span>        Call Sheets("Sheet1").CommandButton2_Click</span>
    <span>    End If</span>
    <span>End Sub</span>
</pre>

Notice that the Check button's click handler is <bold>called</bold> from the function. To make this doable, make your desired function <code>Public</code>.

Sooner or later you will figure it out that the timer does not stop when you press the Check button. To fix this, create another <code>Public</code> boolean variable. Here I name it <code>GetR_Clicked</code> and place it inside the Sheet1's code, where our 2 beloved handlers stay in.

Add the check into <code>updateTimeLabel</code>'s time check, like this:
<pre>
    <span>If (Not wksh.Range("I12").Value = 0) And (Not Sheets("Sheet1").GetR_Clicked)</span>
</pre>

<code>GetR_Clicked</code> also needs to be set to True when you click the Check button, False when you click the Start button.

#4 Protect the sheet

We only allow the user to edit the input cells. And as a part of the huge macro system, Microsuck allows us to (un)protect the sheet.
But first, select the input column, set it to <bold>Unprotected</bold> inside the Format Cells dialog. Now return to our behated code:
<ul>
    <li>Unprotect the sheet with the sheet's <code>.Unprotect()</code>;</li>
    <li>Unlock the user input & check result columns, lock them when the timer goes to zero or Check button gets clicked;</li>
    <li>Unlock the timer's cell before updating its value;</li>
    <li>Lock the sheet with its <code>.Protect()</code> before leaving.</li>
</ul>

#4 Scores table

Another task to make a people know the importance of skills and points.
I choose the first column, from line 25, to be the place of the time my brother start playing the "game" (NOT to confuse with the time that takes him to complete everything).

The third column, from line 25 too, becomes where we can put scores.
A simple loop to jump to the line where we can put the time & score plus 2 simple assignments are enough.

#4 End

The final result is (all in Vietnamese):
<img src="ExcelForKids_Images/Screenshot 2025-04-06 215632.png" width="800"/>

Full code of the sheet:
<pre>
    <span>Public GetR_Clicked As Boolean</span>
    <span></span>
    <span>Private Sub CommandButton1_Click()</span>
    <span>GetR_Clicked = False</span>
    <span>Dim dong As Integer</span>
    <span>dong = 1</span>
    <span></span>
    <span>Sheet1.Unprotect ("a")</span>
    <span>Range("E1", "F21").Clear</span>
    <span>Range("E1", "E21").Locked = False</span>
    <span></span>
    <span>Range("I12").Locked = False</span>
    <span>Range("I12").Value = "00:01:00"</span>
    <span></span>
    <span>Do While dong &lt; 21</span>
    <span>    If WorksheetFunction.RandBetween(1, 2) = 1 Then</span>
    <span>        Sheet1.Cells(dong, 2) = "x"</span>
    <span>        Sheet1.Cells(dong, 1) = WorksheetFunction.RandBetween(3, 9)</span>
    <span>        Sheet1.Cells(dong, 3) = WorksheetFunction.RandBetween(3, 9)</span>
    <span>    Else</span>
    <span>        Sheet1.Cells(dong, 2) = "/"</span>
    <span>        Sheet1.Cells(dong, 3) = WorksheetFunction.RandBetween(3, 9)</span>
    <span>        Sheet1.Cells(dong, 1) = WorksheetFunction.RandBetween(3, 9) * Sheet1.Cells(dong, 3)</span>
    <span>    End If</span>
    <span>    dong = dong + 1</span>
    <span>Loop</span>
    <span></span>
    <span>Application.OnTime Now() + TimeValue("00:00:01"), "updateTimeLabel"</span>
    <span></span>
    <span>Sheet1.Protect ("a")</span>
    <span>End Sub</span>
    <span></span>
    <span>Public Sub CommandButton2_Click()</span>
    <span>GetR_Clicked = True</span>
    <span>Sheet1.Unprotect ("a")</span>
    <span></span>
    <span>Dim dong, kquadung, kquabin As Double</span>
    <span>Dim diem As Integer</span>
    <span></span>
    <span>diem = 100</span>
    <span>dong = 1</span>
    <span></span>
    <span>Do While dong &lt; 21</span>
    <span>    If Sheet1.Cells(dong, 2) = "x" Then</span>
    <span>        kquadung = Sheet1.Cells(dong, 1) * Sheet1.Cells(dong, 3)</span>
    <span>    Else</span>
    <span>        kquadung = WorksheetFunction.Quotient(Sheet1.Cells(dong, 1), Sheet1.Cells(dong, 3))</span>
    <span>    End If</span>
    <span>    </span>
    <span>    kquabin = Sheet1.Cells(dong, 12)</span>
    <span>    </span>
    <span>    If kquabin = kquadung Then</span>
    <span>        Sheet1.Cells(dong, 6) = "Dung"</span>
    <span>    Else</span>
    <span>        Sheet1.Cells(dong, 6) = "Sai. Kqua dung la " &amp; kquadung</span>
    <span>        </span>
    <span>        diem = diem - 5</span>
    <span>    End If</span>
    <span>    </span>
    <span>    dong = dong + 1</span>
    <span>Loop</span>
    <span></span>
    <span>Sheet1.Cells(22, 6) = diem &amp; " / 100"</span>
    <span>Select Case diem</span>
    <span>    Case 100</span>
    <span>        MsgBox Sheet1.Cells(21, 12), vbOKOnly, "From the whole family:"</span>
    <span>    Case 80 To 99</span>
    <span>        MsgBox Sheet1.Cells(22, 12), vbOKOnly, "From the whole family:"</span>
    <span>    Case 40 To 79</span>
    <span>        MsgBox Sheet1.Cells(23, 12), vbOKOnly, "From the whole family:"</span>
    <span>    Case Else</span>
    <span>        MsgBox Sheet1.Cells(24, 12), vbOKOnly, "From the whole family:"</span>
    <span>End Select</span>
    <span></span>
    <span>dong = 25</span>
    <span>Do While Sheet1.Cells(dong, 1) &lt;&gt; ""</span>
    <span>    dong = dong + 1</span>
    <span>Loop</span>
    <span></span>
    <span>Sheet1.Cells(dong, 1) = Now()</span>
    <span>Sheet1.Cells(dong, 3) = diem</span>
    <span></span>
    <span>Sheet1.Protect ("a")</span>
    <span></span>
    <span>End Sub</span>
</pre>

Also the module we created for the timer:
<pre>
    <span>Sub updateTimeLabel()</span>
    <span>Dim wksh As Worksheet</span>
    <span>Set wksh = ThisWorkbook.Sheets("Sheet1")</span>
    <span></span>
    <span>wksh.Unprotect ("a")</span>
    <span></span>
    <span>wksh.Range("I12").Locked = False</span>
    <span></span>
    <span>If (Not wksh.Range("I12").Value = 0) And (Not Sheets("Sheet1").GetR_Clicked) Then</span>
    <span>    wksh.Range("I12").Value = wksh.Range("I12").Value - TimeValue("00:00:01")</span>
    <span>    Application.OnTime Now() + TimeValue("00:00:01"), "updateTimeLabel"</span>
    <span>Else</span>
    <span>    wksh.Range("E1", "F21").Locked = True</span>
    <span>    wksh.Range("I12").Locked = True</span>
    <span>    wksh.Range("I12").Value = "Het gio!"</span>
    <span>    Call Sheets("Sheet1").CommandButton2_Click</span>
    <span>End If</span>
    <span>    </span>
    <span>wksh.Protect ("a")</span>
    <span></span>
    <span>End Sub</span>
</pre>

Thank you for reading!
