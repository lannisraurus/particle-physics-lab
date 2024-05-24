#include "data_colector.cpp"

int main(){
    
    data_colector beta("rvse_betas.txt");
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
    TF1* f = new TF1("f", "[0] / TMath::Sqrt(x)");
    TPaveText* pt = new TPaveText(550, 0.150, 750, 0.250, "user");

    pt->SetTextSize(0.035);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerSize(1);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Energy (keV)");
    g->GetXaxis()->SetLimits(0, 1100);
    g->GetXaxis()->SetNdivisions(-522);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Resolution");
    g->GetYaxis()->SetRangeUser(0, 0.320);
    g->GetYaxis()->SetNdivisions(-416);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    // gStyle->SetOptFit(1); Outro método para adicionar uma label com os valores e incertezas dos parâmetros do fit e o chi quadrado
    pt->AddText(Form("R = \\frac{a}{\\sqrt{E}}"));
    pt->AddText(Form("a = %.6f %c %.6f keV", f->GetParameter(0), 0xB1, f->GetParError(0)));
    //pt->AddText(Form("b = %.6f %c %.6f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.6f", f->GetChisquare()));
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