<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.txt_Receive = New System.Windows.Forms.TextBox()
        Me.btn_ConfigPort = New System.Windows.Forms.Button()
        Me.btn_OpenPort = New System.Windows.Forms.Button()
        Me.Timer_Com = New System.Windows.Forms.Timer(Me.components)
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.btn_Close = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.pb_stat = New System.Windows.Forms.PictureBox()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        CType(Me.pb_stat, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'txt_Receive
        '
        Me.txt_Receive.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txt_Receive.Location = New System.Drawing.Point(257, 185)
        Me.txt_Receive.Name = "txt_Receive"
        Me.txt_Receive.Size = New System.Drawing.Size(158, 26)
        Me.txt_Receive.TabIndex = 1
        '
        'btn_ConfigPort
        '
        Me.btn_ConfigPort.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btn_ConfigPort.Location = New System.Drawing.Point(60, 50)
        Me.btn_ConfigPort.Name = "btn_ConfigPort"
        Me.btn_ConfigPort.Size = New System.Drawing.Size(141, 32)
        Me.btn_ConfigPort.TabIndex = 6
        Me.btn_ConfigPort.Text = "Config Port"
        Me.btn_ConfigPort.UseVisualStyleBackColor = True
        '
        'btn_OpenPort
        '
        Me.btn_OpenPort.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btn_OpenPort.Location = New System.Drawing.Point(60, 94)
        Me.btn_OpenPort.Name = "btn_OpenPort"
        Me.btn_OpenPort.Size = New System.Drawing.Size(141, 32)
        Me.btn_OpenPort.TabIndex = 7
        Me.btn_OpenPort.Text = "Open Port"
        Me.btn_OpenPort.UseVisualStyleBackColor = True
        '
        'Timer_Com
        '
        '
        'SerialPort1
        '
        '
        'btn_Close
        '
        Me.btn_Close.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btn_Close.Location = New System.Drawing.Point(340, 295)
        Me.btn_Close.Name = "btn_Close"
        Me.btn_Close.Size = New System.Drawing.Size(141, 32)
        Me.btn_Close.TabIndex = 8
        Me.btn_Close.Text = "Close"
        Me.btn_Close.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.BackColor = System.Drawing.Color.Transparent
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(253, 141)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(162, 20)
        Me.Label1.TabIndex = 9
        Me.Label1.Text = "Sensor distance [mm]"
        '
        'pb_stat
        '
        Me.pb_stat.BackColor = System.Drawing.Color.Transparent
        Me.pb_stat.Location = New System.Drawing.Point(441, 12)
        Me.pb_stat.Name = "pb_stat"
        Me.pb_stat.Size = New System.Drawing.Size(40, 40)
        Me.pb_stat.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.pb_stat.TabIndex = 11
        Me.pb_stat.TabStop = False
        '
        'PictureBox1
        '
        Me.PictureBox1.Image = Global.PIC32_ChipKit_UART.My.Resources.Resources.GP2Y0A21YK0F
        Me.PictureBox1.InitialImage = CType(resources.GetObject("PictureBox1.InitialImage"), System.Drawing.Image)
        Me.PictureBox1.Location = New System.Drawing.Point(60, 141)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(141, 142)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 10
        Me.PictureBox1.TabStop = False
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(493, 339)
        Me.Controls.Add(Me.pb_stat)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.btn_Close)
        Me.Controls.Add(Me.btn_OpenPort)
        Me.Controls.Add(Me.btn_ConfigPort)
        Me.Controls.Add(Me.txt_Receive)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Form1"
        CType(Me.pb_stat, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents txt_Receive As TextBox
    Friend WithEvents btn_ConfigPort As Button
    Friend WithEvents btn_OpenPort As Button
    Friend WithEvents Timer_Com As Timer
    Friend WithEvents SerialPort1 As IO.Ports.SerialPort
    Friend WithEvents btn_Close As Button
    Friend WithEvents Label1 As Label
    Friend WithEvents PictureBox1 As PictureBox
    Friend WithEvents pb_stat As PictureBox
End Class
