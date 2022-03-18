Public Class Form1
    'Variaveis Globais
    Dim Data_Receive As String
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.Text = "Rs 232 Serie Comunications"
        Me.Icon = New Icon("img\ua_2.ico")
        Me.StartPosition = FormStartPosition.WindowsDefaultLocation
        Me.BackgroundImage = System.Drawing.Image.FromFile("img\bg.jpg")
        pb_stat.Image = System.Drawing.Image.FromFile("img\Grey_Led.png")
        btn_OpenPort.Enabled = False
        txt_Receive.Enabled = False

        'timer
        Timer_Com.Enabled = False
        Timer_Com.Interval = 100

        'textboxs limpas
        txt_Receive.Clear()
    End Sub

    Private Sub btn_Close_Click(sender As Object, e As EventArgs) Handles btn_Close.Click
        'fechar programa
        End
    End Sub

    Private Sub btn_ConfigPort_Click(sender As Object, e As EventArgs) Handles btn_ConfigPort.Click
        'abrir form2 centrada com form1
        FormPortConfig.StartPosition = FormStartPosition.CenterParent
        FormPortConfig.ShowDialog()

        'configuração da porta de comunicação
        If Configuration_Is_Valid = True Then
            With SerialPort1
                .PortName = Port
                .BaudRate = Baud_Rate
                .Parity = Parity
                .DataBits = Data_Bits
                .StopBits = IO.Ports.StopBits.One
                .Encoding = Encoding
            End With
            btn_OpenPort.Enabled = True
        End If

    End Sub

    Private Sub btn_OpenPort_Click(sender As Object, e As EventArgs) Handles btn_OpenPort.Click
        'Abrir/Fechar a porta de comunicação
        If Configuration_Is_Valid = True Then
            If SerialPort1.IsOpen Then
                'fechar porta de comunicação
                SerialPort1.Close()
                'mudar estado dos botões
                btn_OpenPort.Text = "Open Port"
                btn_ConfigPort.Enabled = True
                btn_OpenPort.BackColor = Color.Red
                btn_OpenPort.ForeColor = Color.White
                pb_stat.Image = System.Drawing.Image.FromFile("img\Grey_Led.png")

            Else
                Try
                    'Abrir porta de comunicação
                    SerialPort1.Open()
                    'mudar estado dos botões
                    btn_OpenPort.Text = "Close Port"
                    btn_ConfigPort.Enabled = False
                    btn_OpenPort.BackColor = Color.Green
                    btn_OpenPort.ForeColor = Color.Black
                    txt_Receive.Enabled = True
                    pb_stat.Image = System.Drawing.Image.FromFile("img\Green_Led.png")

                    'ativar timer para leitura de dados
                    Timer_Com.Enabled = True
                Catch ex As Exception
                    MsgBox("Error! Invalid configuration", vbCritical, "Warning")
                    btn_OpenPort.Enabled = False
                End Try

            End If
        Else
            MsgBox("Error! Invalid configuration", vbCritical, "Warning")
            btn_OpenPort.Enabled = False
        End If
    End Sub

    Private Sub SerialPort1_DataReceived(sender As Object, e As IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        'esta private sub e criado no própio código, 
        'localizando a variável serialport1 nos separadores acima
        'escolhendo o evento DATA RECEIVED
        'esta private sub deve conter apenas este código
        'perigo de "crash" de programa
        'leitura de dados automáticamente
        Data_Receive = Data_Receive + SerialPort1.ReadExisting
    End Sub

    Private Sub Timer_Com_Tick(sender As Object, e As EventArgs) Handles Timer_Com.Tick
        'private sub criado com dupo clique no timer da form1
        If Len(Data_Receive) > 0 Then
            txt_Receive.Text = Data_Receive & vbCrLf
            Data_Receive = ""
        End If
    End Sub

End Class
