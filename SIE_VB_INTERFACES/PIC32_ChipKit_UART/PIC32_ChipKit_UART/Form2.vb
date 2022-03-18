Public Class FormPortConfig
    Private Sub FormPortConfig_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        'nome da form2 ou formPortConfig
        Me.Text = "Parâmetros de Comunicação"
        'combobox Portname
        'identificação das portas disponiveis em divice manager
        'para aceder aos device manager
        'cliclar com botao direito no start/iniciar
        'selecionar divice manager (6º da lista)
        'Ver Ports por baixo de Network adapters
        Dim available_ports As Array = IO.Ports.SerialPort.GetPortNames
        Dim n As Integer 'n representa o número de portas

        Try
            CB_PortName.Items.Clear()
            'ciclo de contagem do número de portas 
            'até ao valor total de portas(UBound)
            For n = 0 To UBound(available_ports)
                CB_PortName.Items.Add(available_ports(n))
            Next
            CB_PortName.SelectedIndex = 0 'defenir um valor selecionado por defeito
        Catch ex As Exception
            MsgBox("No COM detected", vbCritical, "Warning")
        End Try


        'combobox parity
        With CB_Parity.Items
            .Clear()
            .Add(IO.Ports.Parity.None)
            .Add(IO.Ports.Parity.Odd)
            .Add(IO.Ports.Parity.Even)
        End With
        CB_Parity.SelectedIndex = 0 'defenir um valor selecionado por defeito

        'combobox baud rate
        With CB_BaudRate.Items
            .Clear()
            .Add("4800")
            .Add("9600")
            .Add("19200")
            .Add("115200")
        End With
        CB_BaudRate.SelectedIndex = 3

        'combobox data bits
        With CB_DataBits.Items
            .Clear()
            .Add("5")
            .Add("6")
            .Add("7")
            .Add("8")
        End With
        CB_DataBits.SelectedIndex = 3

        'combobox stop bits
        With CB_StopBits.Items
            .Clear()
            .Add(IO.Ports.StopBits.One)
            .Add(IO.Ports.StopBits.Two)
        End With
        CB_StopBits.SelectedIndex = 0

        'combobox encoding
        With CB_Encoding.Items
            .Clear()
            .Add("UTF8")
            .Add("UTF32")
        End With
        CB_Encoding.SelectedIndex = 0
    End Sub

    Private Sub btn_Cancel_Click(sender As Object, e As EventArgs) Handles btn_Cancel.Click
        'defenir Configuration_Is_Valid como falso e fechar form2
        ComPortParameters.Configuration_Is_Valid = False
        Me.Close()
    End Sub

    Private Sub btn_OK_Click(sender As Object, e As EventArgs) Handles btn_OK.Click
        'atribui os valores das comboboxs às variaveis public

        'atribuir porta de comunicação
        ComPortParameters.Port = CB_PortName.Text

        'atribuir baud rate
        ComPortParameters.Baud_Rate = CB_BaudRate.Text

        'atribuir paridade
        Select Case CB_Parity.Text
            Case "None"
                ComPortParameters.Parity = IO.Ports.Parity.None
            Case "Even"
                ComPortParameters.Parity = IO.Ports.Parity.Even
            Case "Odd"
                ComPortParameters.Parity = IO.Ports.Parity.Odd
        End Select

        'atribur data bits
        ComPortParameters.Data_Bits = CB_DataBits.Text

        'atribuir stop bits
        Select Case CB_StopBits.Text
            Case "One"
                ComPortParameters.Stop_bits = IO.Ports.StopBits.One
            Case "Two"
                ComPortParameters.Stop_bits = IO.Ports.StopBits.Two
        End Select

        'atribuir encoding
        'ComPortParameters.Encoding = CB_Encoding.Text
        Select Case CB_Encoding.Text
            Case "UTF8"
                ComPortParameters.Encoding = System.Text.Encoding.UTF8
            Case "UTF32"
                ComPortParameters.Encoding = System.Text.Encoding.UTF32
        End Select

        'defenir Configuration_Is_Valid como verdadeiro
        ComPortParameters.Configuration_Is_Valid = True

        'Fechar form2
        Me.Close()
    End Sub
End Class