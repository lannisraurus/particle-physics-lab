// Includes
#include "includes.h"

double fermi(double x, std::vector<double> X, std::vector<double> Y){

    int pos_right = -1, pos_left;

    for (int i = 0; i < X.size(); i++){
        if (X[i] > x) {
            pos_right = i;
            break;
        }
    }

    if (pos_right == -1) return 0;
    pos_left = pos_right - 1;

    double m = (Y[pos_right] - Y[pos_left]) / (X[pos_right] - X[pos_left]);
    double b = Y[pos_right] - m*X[pos_right];

    return m*x + b;
}

// Main Function
int main(){

    double x, y;
    std::vector<double> X, Y, eX, eY;
    std::ifstream in;

    std::vector<double> fermi_x = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};
    std::vector<double> fermi_y = {28.26, 28.19, 27.99, 27.67, 27.25, 26.76, 26.23, 25.66, 25.09, 24.53, 23.98, 22.95, 22.01, 21.17, 20.41, 19.72, 19.10, 18,54};


    in.open("input/betas.txt");
    while(!in.eof()){
        in >> x >> y;

        X.push_back( 4.543*x + 17.8 );
        Y.push_back(y);

        eX.push_back( 0.016*x + 1.6 );
        eY.push_back( sqrt(y) );
    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle("Thalium peak in energies, using bismuth calibration.");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1.75);
    g->GetXaxis()->SetTitle("Energy [keV]");
    g->GetXaxis()->SetLimits(0, 800);
    g->GetXaxis()->SetNdivisions(-520);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);
    g->GetYaxis()->SetTitle("Absolute frequency");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 1100);
    g->GetYaxis()->SetNdivisions(-511);

    g->Draw("");
    C->Update();
    C->SaveAs("output/Tl_Cs_Spectrum.png");
    C->Clear();





    // FIND THE END POINT
    std::vector<double> X2, Y2, eX2, eY2,
                        X3, eX3;

    for (int i = 0; i < X.size(); i++){
        X2.push_back( 0.001 * X[i] / 0.511 );
        eX2.push_back( 0.001 * eX[i] / 0.511 );
    }

    for (int i = 0; i < Y.size(); i++){

        if ( Y[i] != 0 ){
            double W = X2[i] + 1. ;
            double P = sqrt( W*W - 1. );
            double G = fermi( P , fermi_x, fermi_y);
            
            Y2.push_back (   (1./W) * sqrt( Y[i] / G )   );
            X3.push_back( X2[i] );
            eX3.push_back( eX2[i] );

            double errY = sqrt(1./G)*sqrt(   eY[i]*eY[i]/(4*Y[i]*W*W)     +     Y[i]*eX2[i]*eX2[i]/(W*W*W*W)   );
            eY2.push_back( errY );
        }
    }

    TGraphErrors* g2 = new TGraphErrors(X3.size(), X3.data(), Y2.data(), eX3.data(), eY2.data());

    g2->SetTitle("");
    g2->SetMarkerStyle(4);
    g2->SetMarkerColor(kAzure+2);
    g2->SetLineColor(kBlue+2);
    g2->SetLineWidth(1.75);
    g2->GetXaxis()->SetTitle("E = Energy [MeV] / 0.511 MeV");
    g2->GetXaxis()->SetLimits(0, 1.6);
    g2->GetXaxis()->SetNdivisions(-510);
    g2->GetXaxis()->SetLabelSize(0.028);
    g2->GetXaxis()->SetTickLength(-0.04);
    g2->GetXaxis()->SetLabelOffset(0.033);
    g2->GetXaxis()->SetTitleOffset(1.3);
    g2->GetYaxis()->SetTitle(" (1/(E+1))sqrt( N / G(Z,W) ) ");
    g2->GetYaxis()->SetLabelSize(0.028);
    g2->GetYaxis()->SetRangeUser(0, 5);
    g2->GetYaxis()->SetNdivisions(-510);

    g2->Draw("");
    C->Update();
    C->SaveAs("output/endpoint.png");
    C->Clear();


    std::vector<double> Xl, Yl, eXl, eYl;
    for (int i = 45; i < X3.size() - 10; i++){
        Xl.push_back ( X3[i] );
        Yl.push_back ( Y2[i] );
        eXl.push_back ( eX3[i] );
        eYl.push_back ( eY2[i] );
    }

    TGraphErrors* g3 = new TGraphErrors(Xl.size(), Xl.data(), Yl.data(), eXl.data(), eYl.data());
    TF1* f = new TF1("f", "[0]*x + [1]",0,10);
    f->SetParameter(0,-4.565);
    f->SetParameter(1,6.695);
    f->SetLineColor(kOrange);
    f->SetLineWidth(3);

    g3->SetTitle("");
    g3->SetMarkerStyle(4);
    g3->SetMarkerColor(kAzure+2);
    g3->SetLineColor(kBlue+2);
    g3->SetLineWidth(1.75);
    g3->GetXaxis()->SetTitle("E = Energy [MeV] / 0.511 MeV");
    g3->GetXaxis()->SetLimits(0.4, 1.6);
    g3->GetXaxis()->SetNdivisions(-510);
    g3->GetXaxis()->SetLabelSize(0.028);
    g3->GetXaxis()->SetTickLength(-0.04);
    g3->GetXaxis()->SetLabelOffset(0.033);
    g3->GetXaxis()->SetTitleOffset(1.3);
    g3->GetYaxis()->SetTitle(" (1/(E+1))sqrt( N / G(Z,W) ) ");
    g3->GetYaxis()->SetLabelSize(0.028);
    g3->GetYaxis()->SetRangeUser(0, 5);
    g3->GetYaxis()->SetNdivisions(-510);

    g3->Fit("f");


    TPaveText* pt = new TPaveText(1.12, 3, 1.6, 4, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.10f %c %.10f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.10f %c %.10f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.10f", f->GetChisquare()));
    pt->AddText(Form("Number of points = %i", int(Xl.size())));
    

    
    g3->Draw("AP");
    f->Draw("same");
    pt->Draw("same");
    
    std::cout << "Chi squared: " << f->GetChisquare() << "\n";




    
    C->Update();
    C->SaveAs("output/endpoint2.png");
    C->Clear();


}
