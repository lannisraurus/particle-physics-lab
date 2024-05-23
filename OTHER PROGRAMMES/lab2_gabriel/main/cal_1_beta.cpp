#include "data_colector.cpp"

int main(){
    
    data_colector beta("cal_1_beta.txt");
    vector<double> x = beta.get_a_certain_col(1);
    vector<double> ex = beta.get_a_certain_col(2);
    vector<double> y = beta.get_a_certain_col(3);
    vector<double> ey = beta.get_a_certain_col(4);
    Int_t points_numb = x.size();

    double* x_ptr = &x[0];
    double* ex_ptr = &ex[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_ptr, ey_ptr);
    TF1* f = new TF1("f", "[0] * x + [1]");
    TPaveText* pt = new TPaveText(50, 0.7, 150, 1.1, "user");

    f->SetParameter(0, 0.00431);
    f->SetParameter(1, 0);

    pt->SetTextSize(0.035);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerSize(1);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(0, 275);
    g->GetXaxis()->SetNdivisions(-20511);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Energy (pulser units)");
    g->GetYaxis()->SetRangeUser(0, 1.3);
    g->GetYaxis()->SetNdivisions(-513);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    // gStyle->SetOptFit(1); Outro método para adicionar uma label com os valores e incertezas dos parâmetros do fit e o chi quadrado
    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.6f %c %.6f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.4f %c %.4f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->Draw();

    C->Update();
    //C->SaveAs("cal_1_beta_corr.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete pt;
    delete A;

    return 0;
}