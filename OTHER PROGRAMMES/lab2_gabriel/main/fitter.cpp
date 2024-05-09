#include "data_colector.cpp"

int main(){

    data_colector test("test.txt");

    // 1. Preenche um vector<vector<double>> "data", uma variável de "test", em que cada um dos seus vector<double> fica preenchido 
    // com os dados de uma das colunas do documento "test.txt". O vector<vector<double>> "data" tem os seu vetores automaticamente 
    // printados em colunas num novo documento cujo nome é "new_" + nome do documento que lhe deu origem.

    // 2. "test.get_data()" retorna "data".

    // 3. Considera-se que uma linha tem dados a serem coletados (é "colectable") se o seu primeiro elemento for do tipo numérico.
    // Um elemento de uma linha é designado por "iss" e corresponde a um conjunto de caractéres que termina quando se encontra um 
    // espaço ou uma troca de linha. Antes de se iniciar a análise das linhas todas as vírgulas foram substituídas por pontos. Este 
    // método que defini funciona com o "copy" e "paste" de colunas do excell num bloco de notas e com os ficheiros que guardamos com a disquete 
    // quando abertos com o bloco de notas.

    string name = "h";
    string title = "Histogram";
    Int_t bins_numb = 20;
    Double_t min_val = test.get_a_certain_col_min(2); // Retorna o menor valor da 2ª coluna do documento.
    Double_t max_val = test.get_a_certain_col_max(2); // Retorna o maior valor da 2ª coluna do documento.
    Double_t dx = min_val / 1000000;
    vector<double> data = test.get_a_certain_col(2); // Retorna um vector<double> com os dados da 2ª coluna do documento.

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TH1* h = new TH1D(name.c_str(), title.c_str(), bins_numb, min_val - dx, max_val + dx);

    for (double val : data){

        h->Fill(val);
    }
    
    TF1* f = new TF1("f", "1 / ([std_dev] * TMath::Sqrt(2 * TMath::Pi())) * TMath::Exp(-0.5 * pow((x - [mean]) / [std_dev], 2))", 
    min_val, max_val);

    // Em vez de definir a função manualmente, como fiz acima, podia ter usado a função predifinida "gaus", constituída por 3 parâmetros: 
    // gaus(x) com x = média (ou amplitude) (0), média (1) e desvio padrão (2);

    f->SetParameter("mean", 0.5);
    f->SetParameter("std_dev", 0.1);

    h->Draw();
    h->Fit("f", "R"); // Com h->Fit("gaus") nem precisava de criar f.
    h->SetLineColor(kBlack);
    h->SetFillColor(kWhite);
    h->GetXaxis()->SetTitle("Pulse voltage / V (the numbers displayed on the axis represent the upper limit of each bin)");
    h->GetXaxis()->SetTickLength(-0.02);

    for (int i = 1; i <= bins_numb; i++){
        
        h->GetXaxis()->SetBinLabel(i, Form("%.3f", h->GetBinLowEdge(i) + h->GetBinWidth(i)));
    }

    h->GetYaxis()->SetTitle("Absolute frequency");
    h->GetYaxis()->SetRangeUser(0, 8);
    h->GetYaxis()->SetNdivisions(8);
    h->GetYaxis()->SetTickLength(0.008);
    C->Update();
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete h;
    delete f;
    delete A; // Tem que ser o último a ser apagado.

    return 0;
}