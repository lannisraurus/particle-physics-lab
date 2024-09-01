// Includes
#include "includes.h"

// Main Function
int main(){

    double x, y;
    std::vector<double> X, Y, eX, eY;
    std::vector<double> Xd, Yd, eXd, eYd;
    std::ifstream in;

    int bound_l = 475, bound_r = 565;

    in.open("input/chumbo.txt");
    while(!in.eof()){

        in >> x >> y;

        if (bound_l <= x && x <= bound_r){
            Xd.push_back(x);
            Yd.push_back(y);
            eXd.push_back( 0 );  
            eYd.push_back( sqrt(y) );
        }

        X.push_back(x);
        Y.push_back(y);
        eX.push_back( 0 );  
        eY.push_back( sqrt(y) );
        

    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());
    TGraphErrors* gd = new TGraphErrors(Xd.size(), Xd.data(), Yd.data(), eXd.data(), eYd.data());

    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kGreen+2);
    g->SetLineColor(kGreen+2);
    g->SetLineWidth(1.75);

    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(0, 1024);
    g->GetXaxis()->SetNdivisions(30);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Counts");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 400);
    g->GetYaxis()->SetNdivisions(-520);

    TF1* f = new TF1("f", "gaus",bound_l,bound_r);



    gd->SetTitle("");
    gd->SetMarkerStyle(4);
    gd->SetMarkerColor(kRed+2);
    gd->SetLineColor(kRed+2);
    gd->SetLineWidth(1.75);

    gd->GetXaxis()->SetTitle("Channel");
    gd->GetXaxis()->SetLimits(0, 1024);
    gd->GetXaxis()->SetNdivisions(30);
    gd->GetXaxis()->SetLabelSize(0.028);
    gd->GetXaxis()->SetTickLength(-0.04);
    gd->GetXaxis()->SetLabelOffset(0.033);
    gd->GetXaxis()->SetTitleOffset(1.3);

    gd->GetYaxis()->SetTitle("Counts");
    gd->GetYaxis()->SetLabelSize(0.028);
    gd->GetYaxis()->SetRangeUser(0, 400);
    gd->GetYaxis()->SetNdivisions(-520);



    f->SetLineColor(kBlue);
    f->SetLineWidth(2);

    gd->Fit("f");

    TPaveText* pt = new TPaveText(750, 350, 1000, 250, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("Gaussian Fit"));
    pt->AddText(Form("A = %.1f %c %.1f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("#mu = %.2f %c %.2f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#sigma = %.3f %c %.3f", f->GetParameter(2), 0xB1, f->GetParError(2)));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->AddText(Form("Number of points = %ld", Xd.size() ));

    f->Draw();
    g->Draw("AC");
    gd->Draw("same");
    pt->Draw("same");
    
    C->Update();
    C->SaveAs("output/CHUMBO.png");
    C->Clear();


}
