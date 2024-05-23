// Includes
#include "includes.h"

// Draw Graph
void drawGraphWithErrors(std::vector<double> X, std::vector<double> eX, std::vector<double> Y,
                         std::vector<double> eY, std::string title, std::string xAxis, std::string yAxis,
                         double x_min, double x_max, double y_min, double y_max, double xDiv, double yDiv,
                         std::string drawSettings
                        )
{
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle(title.c_str());
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(2.50);
    
    g->GetXaxis()->SetTitle(xAxis.c_str());
    g->GetXaxis()->SetLimits(x_min, x_max);
    g->GetXaxis()->SetNdivisions(xDiv);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);
    
    g->GetYaxis()->SetTitle(yAxis.c_str());
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 10000);
    g->GetYaxis()->SetNdivisions(yDiv);

    g->Draw("");

}

// Fit and Draw gaussian curves
void fitAndDrawGaussianCurves(std::vector<double> X, std::vector<double> eX, std::vector<double> Y,
                              std::vector<double> eY, double min_energy, double max_energy, double x_incr, double y_incr
                             )
{
    std::vector<double> new_X, new_Y, new_eX, new_eY;
    double localMax = -1;
    double max = -1;
    for (int i = 0; i < X.size(); i++){
        if (Y[i] > max) max = Y[i];
        if (min_energy <= X[i] && X[i] <= max_energy){
            new_X.push_back(X[i]);
            new_Y.push_back(Y[i]);
            new_eX.push_back(eX[i]);
            new_eY.push_back(eY[i]);
            if (Y[i] > localMax) localMax = Y[i];
            std::cout << new_X.back() << " , " << new_Y.back() << "\n";
        }
    }

    std::cout << "local max " << localMax << "\n";

    TGraphErrors* g = new TGraphErrors(new_X.size(), new_X.data(), new_Y.data(), new_eX.data(), new_eY.data());
    TF1* f = new TF1("f", "gaus", 0 , 1100);

    f->SetLineColor(kRed);
    f->SetLineWidth(2.5);

    g->Fit("f");

    TPaveText* pt = new TPaveText(min_energy + x_incr*max/100., localMax + (10.+y_incr)*max/100., max_energy + x_incr*max/100., localMax + (25.+y_incr)*max/100., "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("A = %.2f %c %.2f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("#mu = %.2f %c %.2f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#sigma = %.2f %c %.2f", f->GetParameter(2), 0xB1, f->GetParError(2)));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    
    g->SetLineColor(kOrange+1);
    g->SetLineWidth(2.50);

    g->Draw("same");
    pt->Draw();

}

// Main Function
int main(){

    int IMAGE_SCALING = 200;

    double x, y;
    std::vector<double> X, Y, eX, eY;
    std::ifstream in;

    in.open("input/betas_2.txt");
    while(!in.eof()){
        in >> x >> y;

        X.push_back( 4.543*x + 17.8 );
        Y.push_back(y);

        eX.push_back( 0.016*x + 1.6 );
        eY.push_back( sqrt(y) );
    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*IMAGE_SCALING, 9*IMAGE_SCALING);

    drawGraphWithErrors(X,eX,Y,eY,"Bismuth-207 Spectrum","Energy [keV]","Counts",0,1100,0,10000,-522,-520,"");



    fitAndDrawGaussianCurves(X,eX,Y,eY,45,70, 0.35,-15);
    fitAndDrawGaussianCurves(X,eX,Y,eY,79,98, 0.23,-25);

    fitAndDrawGaussianCurves(X,eX,Y,eY,475,500, 0,-5);
    
    fitAndDrawGaussianCurves(X,eX,Y,eY,545,570, 0 ,-5);
    fitAndDrawGaussianCurves(X,eX,Y,eY,567,590, 0.2,-10);

    fitAndDrawGaussianCurves(X,eX,Y,eY,960,990, -1.5,-10);
    
    fitAndDrawGaussianCurves(X,eX,Y,eY,1035,1055, -0.1,10);
    fitAndDrawGaussianCurves(X,eX,Y,eY,1053,1070, 0.06,-5);





    C->Update();
    C->SaveAs("output/Bi_Spectrum.png");
    C->Clear();

}
