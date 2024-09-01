// Includes
#include "includes.h"


double Skewed_Gauss(double *x, double *p)
{
  double shift     = p[0];   // first argument is shift
  double spread    = p[1];   // second argument is spread
  double skewness  = p[2];   // third argument is skewness
  double amplitude = p[3];   // fourth argument is amplitude

  double argument = (x[0] - shift)/ spread;

  double Norm_gaus = TMath::Gaus(argument, 0.0, 1.0, true);
  double CDF       = 0.5 * (1 + erf(skewness* argument/sqrt(2)) );

  return amplitude* Norm_gaus* CDF;
}


// Main Function
int main(){

    double x, y;
    std::vector<double> X, Y, eX, eY;
    std::vector<double> X1, Y1, eX1, eY1;
    std::vector<double> X2, Y2, eX2, eY2;
    std::ifstream in;

    in.open("input/ajustes.txt");
    while(!in.eof()){
        in >> x >> y;
        // 1.52249*x + 0.959
        // 0.00029*x + 0.066
        X.push_back(x);
        Y.push_back(y);
        eX.push_back( 0 );  
        eY.push_back( sqrt(y) );
    }

    for (int i = 0; i < X.size(); i++) {
        if (240 <= X[i] && X[i] <= 350){
            X1.push_back(X[i]);
            Y1.push_back(Y[i]);
            eX1.push_back(eX[i]);
            eY1.push_back(eY[i]);
        }
        if (120 <= X[i] && X[i] <= 150){
            X2.push_back(X[i]);
            Y2.push_back(Y[i]);
            eX2.push_back(eX[i]);
            eY2.push_back(eY[i]);
        }
    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());
    TGraphErrors* g1 = new TGraphErrors(X1.size(), X1.data(), Y1.data(), eX1.data(), eY1.data());
    TGraphErrors* g2 = new TGraphErrors(X2.size(), X2.data(), Y2.data(), eX2.data(), eY2.data());

    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kRed+2);
    g->SetLineColor(kGreen+2);
    g->SetLineWidth(1.75);
    g->SetMarkerSize(0.8);

    g->GetXaxis()->SetTitle("Energy [keV]");
    g->GetXaxis()->SetLimits(0, 750);
    g->GetXaxis()->SetNdivisions(-515);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Counts");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 550);
    g->GetYaxis()->SetNdivisions(-511);

    g1->SetMarkerStyle(4);
    g1->SetMarkerColor(kBlue+2);
    g1->SetLineColor(kBlue+2);
    g1->SetLineWidth(1.75);
    g1->SetMarkerSize(0.8);

    g2->SetMarkerStyle(4);
    g2->SetMarkerColor(kBlue+2);
    g2->SetLineColor(kBlue+2);
    g2->SetLineWidth(1.75);
    g2->SetMarkerSize(0.8);

    TF1 * f = new TF1("f"," [0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Erfc( (x - [1]) / TMath::Sqrt(2*[2]) ) ",0,1200);
    TF1 * f2 = new TF1("f2"," [0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Erfc( ([1] - x) / TMath::Sqrt(2*[2]) ) ",0,1200);

    f->SetLineColor(kPink);
    f->SetLineWidth(2);

    f2->SetLineColor(kPink);
    f2->SetLineWidth(2);

    f->SetParameters(10,300,50,20);
    f2->SetParameters(50,125,50,15);

    g1->Fit("f");
    g2->Fit("f2");

    TPaveText* pt1 = new TPaveText(350, 350, 450, 500, "user");
    TPaveText* pt2 = new TPaveText(100, 350, 200, 500, "user");

    pt1->SetTextSize(0.03);
    pt1->SetFillColor(0);
    pt1->SetTextAlign(12);
    pt1->SetTextFont(42);

    pt1->AddText(Form("Compton Edge Fit"));
    pt1->AddText(Form("#alpha = %.1f %c %.1f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt1->AddText(Form("#beta = %.2f %c %.2f", f->GetParameter(3), 0xB1, f->GetParError(3)));
    pt1->AddText(Form("#sigma = (%.1f %c %.1f)#upoint10^{2}", f->GetParameter(2)*0.01, 0xB1, f->GetParError(2)*0.01));
    pt1->AddText(Form("Ec = %.1f %c %.1f", f->GetParameter(1), 0xB1, f->GetParError(1)));

    pt1->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt1->AddText(Form("Number of points = %ld", X1.size() ));




    pt2->SetTextSize(0.03);
    pt2->SetFillColor(0);
    pt2->SetTextAlign(12);
    pt2->SetTextFont(42);

    pt2->AddText(Form("Backscattering Fit"));
    pt2->AddText(Form("#alpha = %.1f %c %.1f", f2->GetParameter(0), 0xB1, f2->GetParError(0)));
    pt2->AddText(Form("#beta = %.1f %c %.1f", f2->GetParameter(3), 0xB1, f2->GetParError(3)));
    pt2->AddText(Form("#sigma = %.1f %c %.1f", f2->GetParameter(2), 0xB1, f2->GetParError(2)));
    pt2->AddText(Form("Ec = %.1f %c %.1f", f2->GetParameter(1), 0xB1, f2->GetParError(1)));

    pt2->AddText(Form("#chi^{2} = %.2f", f2->GetChisquare()));
    pt2->AddText(Form("Number of points = %ld", X2.size() ));





    g->Draw();
    g1->Draw("same");
    g2->Draw("same");

    pt1->Draw("same");
    pt2->Draw("same");
    
    C->Update();
    C->SaveAs("output/CS_AJUSTES.png");
    C->Clear();
}
