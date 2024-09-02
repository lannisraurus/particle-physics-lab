// Includes
#include "includes.h"

void chnToUP(double chn, double echn){

    double mev = 7.490*0.001*chn - 0.01*1.525;
    double err = sqrt( 7.490*7.490*0.001*0.001*echn*echn + chn*chn*0.012*0.012*0.001*0.001 + 0.07*0.07*0.01*0.01 );

    std::cout << "Channel: " << chn << " +- " << echn << ", Energy: " << mev << " +- " << err << "\n";
}

void chnToMeV(double chn, double echn){

    double mev = 7.733*0.001*chn - 0.01*1.572;
    double err = sqrt( 7.733*7.733*0.001*0.001*echn*echn + chn*chn*0.018*0.018*0.001*0.001 + 0.072*0.072*0.01*0.01 );

    std::cout << "Channel: " << chn << " +- " << echn << ", Energy: " << mev << " +- " << err << "\n";
}

void AF(double a, double ea, double f, double ef){

    double m = a*f;
    double em = sqrt( a*a*ef*ef + f*f*ea*ea );

    std::cout << m << " +- " << em << "\n";

}

// Main Function
int main(){

    double x, y, ex, ey;
    std::vector<double> X, Y, eX, eY;
    std::ifstream in;

    in.open("input/alfas_3.txt");
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
    g->GetXaxis()->SetLimits(400, 750);
    g->GetXaxis()->SetNdivisions(-910);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Energy [MeV]");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(3.0, 5.6);
    g->GetYaxis()->SetNdivisions(-510);

    TF1* f = new TF1("f", "[0]*x + [1]",0,800);

    f->SetLineColor(kBlue);
    f->SetLineWidth(2);

    g->Fit("f");

    TPaveText* pt = new TPaveText(430, 5.0, 500, 4.0, "user");

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
    C->SaveAs("output/lin_fit_2.png");
    C->Clear();

    chnToUP(687.92,0.04);

    AF( 7.49*0.001, 0.012*0.001, 1.0324, 0.0017 );
    AF( 1.523*0.01, 0.07*0.01, 1.0324, 0.0017 );

    std::cout << "\n\n\n";

    chnToUP(687.92,0.04);
    chnToUP(503.36,0.13);
    chnToUP(699.88,0.05);
    chnToUP(555.28,0.03);

    std::cout << "\n\n\n";

    chnToMeV(687.92,0.04);
    chnToMeV(503.36,0.13);
    chnToMeV(699.88,0.05);
    chnToMeV(555.28,0.03);

}
