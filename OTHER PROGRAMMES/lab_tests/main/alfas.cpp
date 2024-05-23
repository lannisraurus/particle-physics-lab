// Includes
#include "includes.h"

// Main Function
int main(){

    double x, y, ex, ey;
    std::vector<double> X, Y, eX, eY;
    std::ifstream in;

    in.open("input/alfas.txt");
    while(!in.eof()){

        in >> x >> ex >> y >> ey;

        X.push_back(x);
        Y.push_back(y);
        eX.push_back(ex);
        eY.push_back(ey);

        std::cout << X.back() << " " << eX.back() << " " << Y.back() << " " << eY.back() << "\n";

    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle("Corrected linear fit");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1.75);

    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(200, 650);
    g->GetXaxis()->SetNdivisions(-910);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Energy [MeV]");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(4.75, 5.75);
    g->GetYaxis()->SetNdivisions(-510);

    TF1* f = new TF1("f", "[0]*x + [1]",0,800);

    f->SetLineColor(kBlue);
    f->SetLineWidth(2);

    g->Fit("f");

    TPaveText* pt = new TPaveText(245, 5.35, 335, 5.65, "user");

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
    C->SaveAs("output/lin_fit.png");
    C->Clear();


}
