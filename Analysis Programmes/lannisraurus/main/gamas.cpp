// Includes
#include "includes.h"

// Main Function
int main(){

    std::vector<double> X, Y, eX, eY;

    X = {427.27, 20.39, 758.36, 852.22};
    eX = {0.085, 0.028, 0.14, 0.16};
    Y = {662, 32, 1173, 1333};
    eY = {0, 0, 0, 0};

    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle("Linear fit");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1.75);

    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(0, 900);
    g->GetXaxis()->SetNdivisions(-910);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Energy [keV]");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 1400);
    g->GetYaxis()->SetNdivisions(-510);

    TF1* f = new TF1("f", "[0]*x + [1]",0,1000);
    f->SetParameters(1.65, 0);

    f->SetLineColor(kBlue);
    f->SetLineWidth(2);

    g->Fit("f");

    TPaveText* pt = new TPaveText(90, 840, 270, 1120, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.10f %c %.10f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.10f %c %.10f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.10f", f->GetChisquare()));
    
    
    f->Draw();
    g->Draw("AP");
    pt->Draw("same");
    
    C->Update();
    C->SaveAs("output/lin_fit_gamas.png");
    C->Clear();


}
