// Includes
#include "includes.h"

// Main Function
int main(){

    std::vector<double> E_teo = { 32, 662, 1173, 1333, 184.3, 477.7, 963, 1118, 1460.82, 121.78, 344.27, 778.90, 964.1 },
                        E_exp = { 32, 662, 1173, 1333, 186.1, 473.8, 940, 1088, 1461.77, 127.81, 350.10, 778.52, 962.0 },

                        eE_teo = {},
                        eE_exp = {0, 0, 0, 0, 2.1, 2.2, 12, 28, 0.68, 0.12, 0.16, 0.97, 1.0}; 

    for (int i = 0 ; i < E_teo.size(); i++) eE_teo.push_back(0);

    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(E_teo.size(), E_teo.data(), E_exp.data(), eE_teo.data(), eE_exp.data());

    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlue+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1);
    g->SetMarkerSize(1.75);

    g->GetXaxis()->SetTitle("Theoretical Energy [keV]");
    g->GetXaxis()->SetLimits(0, 1500);
    g->GetXaxis()->SetNdivisions(-515);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Experimental Energy [keV]");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 1500);
    g->GetYaxis()->SetNdivisions(-515);

    TF1* f = new TF1("f", "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x", -100, 2000);
    f->SetParameters(1,1,1,1,1);
    f->SetLineColor(kRed);
    f->SetLineWidth(2);

    g->Fit("f");

    TPaveText* pt = new TPaveText(100, 700, 400, 1400, "user");

    pt->SetTextSize(0.04);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("y = a + bx + cx^2 + dx^3 + ex^4"));
    pt->AddText(Form("a = %.2f %c %.2f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.4f %c %.4f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("c = %.7f %c %.7f", f->GetParameter(2), 0xB1, f->GetParError(2)));
    pt->AddText(Form("d = %.10f %c %.10f", f->GetParameter(3), 0xB1, f->GetParError(3)));
    pt->AddText(Form("e = (%.2f %c %.2f)#upoint10^{-10}", f->GetParameter(4)*10E10, 0xB1, f->GetParError(4)*10E10));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->AddText(Form("Number of points = %ld", E_teo.size() ));

    g->Draw("AP");
    pt->Draw("same");
    
    C->Update();
    C->SaveAs("output/SISTEMATICO.png");
    C->Clear();

}
