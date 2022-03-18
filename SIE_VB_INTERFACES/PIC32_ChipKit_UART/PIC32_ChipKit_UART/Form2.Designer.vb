<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class FormPortConfig
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(FormPortConfig))
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.CB_PortName = New System.Windows.Forms.ComboBox()
        Me.CB_BaudRate = New System.Windows.Forms.ComboBox()
        Me.CB_Parity = New System.Windows.Forms.ComboBox()
        Me.btn_Cancel = New System.Windows.Forms.Button()
        Me.btn_OK = New System.Windows.Forms.Button()
        Me.CB_DataBits = New System.Windows.Forms.ComboBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.CB_StopBits = New System.Windows.Forms.ComboBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.CB_Encoding = New System.Windows.Forms.ComboBox()
        Me.Encouding = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(39, 36)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(84, 20)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Port Name"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(39, 70)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(86, 20)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "Baud Rate"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.Location = New System.Drawing.Point(39, 104)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(48, 20)
        Me.Label3.TabIndex = 2
        Me.Label3.Text = "Parity"
        '
        'CB_PortName
        '
        Me.CB_PortName.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CB_PortName.FormattingEnabled = True
        Me.CB_PortName.Location = New System.Drawing.Point(133, 28)
        Me.CB_PortName.Name = "CB_PortName"
        Me.CB_PortName.Size = New System.Drawing.Size(121, 28)
        Me.CB_PortName.TabIndex = 3
        '
        'CB_BaudRate
        '
        Me.CB_BaudRate.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CB_BaudRate.FormattingEnabled = True
        Me.CB_BaudRate.Location = New System.Drawing.Point(133, 62)
        Me.CB_BaudRate.Name = "CB_BaudRate"
        Me.CB_BaudRate.Size = New System.Drawing.Size(121, 28)
        Me.CB_BaudRate.TabIndex = 4
        '
        'CB_Parity
        '
        Me.CB_Parity.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CB_Parity.FormattingEnabled = True
        Me.CB_Parity.Location = New System.Drawing.Point(133, 96)
        Me.CB_Parity.Name = "CB_Parity"
        Me.CB_Parity.Size = New System.Drawing.Size(121, 28)
        Me.CB_Parity.TabIndex = 5
        '
        'btn_Cancel
        '
        Me.btn_Cancel.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btn_Cancel.Location = New System.Drawing.Point(271, 199)
        Me.btn_Cancel.Name = "btn_Cancel"
        Me.btn_Cancel.Size = New System.Drawing.Size(75, 27)
        Me.btn_Cancel.TabIndex = 6
        Me.btn_Cancel.Text = "Cancel"
        Me.btn_Cancel.UseVisualStyleBackColor = True
        '
        'btn_OK
        '
        Me.btn_OK.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btn_OK.Location = New System.Drawing.Point(271, 166)
        Me.btn_OK.Name = "btn_OK"
        Me.btn_OK.Size = New System.Drawing.Size(75, 26)
        Me.btn_OK.TabIndex = 7
        Me.btn_OK.Text = "OK"
        Me.btn_OK.UseVisualStyleBackColor = True
        '
        'CB_DataBits
        '
        Me.CB_DataBits.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CB_DataBits.FormattingEnabled = True
        Me.CB_DataBits.Location = New System.Drawing.Point(133, 130)
        Me.CB_DataBits.Name = "CB_DataBits"
        Me.CB_DataBits.Size = New System.Drawing.Size(121, 28)
        Me.CB_DataBits.TabIndex = 9
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.Location = New System.Drawing.Point(39, 138)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(75, 20)
        Me.Label4.TabIndex = 8
        Me.Label4.Text = "Data Bits"
        '
        'CB_StopBits
        '
        Me.CB_StopBits.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CB_StopBits.FormattingEnabled = True
        Me.CB_StopBits.Location = New System.Drawing.Point(133, 164)
        Me.CB_StopBits.Name = "CB_StopBits"
        Me.CB_StopBits.Size = New System.Drawing.Size(121, 28)
        Me.CB_StopBits.TabIndex = 11
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label5.Location = New System.Drawing.Point(39, 172)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(74, 20)
        Me.Label5.TabIndex = 10
        Me.Label5.Text = "Stop Bits"
        '
        'CB_Encoding
        '
        Me.CB_Encoding.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CB_Encoding.FormattingEnabled = True
        Me.CB_Encoding.Location = New System.Drawing.Point(133, 198)
        Me.CB_Encoding.Name = "CB_Encoding"
        Me.CB_Encoding.Size = New System.Drawing.Size(121, 28)
        Me.CB_Encoding.TabIndex = 13
        '
        'Encouding
        '
        Me.Encouding.AutoSize = True
        Me.Encouding.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Encouding.Location = New System.Drawing.Point(39, 206)
        Me.Encouding.Name = "Encouding"
        Me.Encouding.Size = New System.Drawing.Size(76, 20)
        Me.Encouding.TabIndex = 12
        Me.Encouding.Text = "Encoding"
        '
        'FormPortConfig
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(378, 250)
        Me.Controls.Add(Me.CB_Encoding)
        Me.Controls.Add(Me.Encouding)
        Me.Controls.Add(Me.CB_StopBits)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.CB_DataBits)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.btn_OK)
        Me.Controls.Add(Me.btn_Cancel)
        Me.Controls.Add(Me.CB_Parity)
        Me.Controls.Add(Me.CB_BaudRate)
        Me.Controls.Add(Me.CB_PortName)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "FormPortConfig"
        Me.Text = "Form2"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents CB_PortName As ComboBox
    Friend WithEvents CB_BaudRate As ComboBox
    Friend WithEvents CB_Parity As ComboBox
    Friend WithEvents btn_Cancel As Button
    Friend WithEvents btn_OK As Button
    Friend WithEvents CB_DataBits As ComboBox
    Friend WithEvents Label4 As Label
    Friend WithEvents CB_StopBits As ComboBox
    Friend WithEvents Label5 As Label
    Friend WithEvents CB_Encoding As ComboBox
    Friend WithEvents Encouding As Label
End Class
