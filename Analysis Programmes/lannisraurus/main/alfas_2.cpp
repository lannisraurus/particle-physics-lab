// Includes
#include "includes.h"


void deltaChnMev(double fwhm, double e_fwhm){
    double mev = 1.7827*fwhm*0.001;
    double err = sqrt( 1.7827*1.7827*0.001*0.001*e_fwhm*e_fwhm + 0.0092*0.0092*0.001*0.001*fwhm*fwhm );
    std::cout << "FWHM: " << fwhm << " +- " << e_fwhm << ", Energy: " << mev << " +- " << err << "\n";
}

void chnToMev(double chn, double echn){

    double mev = 1.7827*0.001*chn + 4.6403;
    double err = sqrt( 1.7827*1.7827*0.001*0.001*echn*echn + chn*chn*0.0092*0.0092*0.001*0.001 + 0.006*0.006 );

    std::cout << "Channel: " << chn << " +- " << echn << ", Energy: " << mev << " +- " << err << "\n";
}

void resol(double E, double eE, double dE, double edE){
    double R = dE/E;
    double eR = sqrt( edE*edE/(E*E) + dE*dE*eE*eE/(E*E*E*E) );
    std::cout << "Energy: " << E << "   R: " << R << " +- " << eR << "\n";
}


// Main Function
int main(){

    double x, y;
    std::vector<double> X, Y;
    std::ifstream in;

    in.open("input/alfas_2.txt");
    while(!in.eof()){

        in >> x >> y;

        X.push_back( 1.7827*0.001*x + 4.6403 );
        Y.push_back( y );

    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraph* g = new TGraph(X.size(), X.data(), Y.data());

    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1.75);

    g->GetXaxis()->SetTitle("Energy [MeV]");
    g->GetXaxis()->SetLimits(5.3, 5.6);
    g->GetXaxis()->SetNdivisions(-515);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Counts");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 13000);
    g->GetYaxis()->SetNdivisions(-510);

    g->Draw("AL*");
    
    C->Update();
    C->SaveAs("output/spectrum.png");
    C->Clear();

    std::cout << "Amerício\n";
    chnToMev(477.59, 0.01);
    chnToMev(453.05, 0.04);
    chnToMev(421.81, 0.09);
    std::cout << "Polónio\n";
    chnToMev(372.45, 0.11);
    std::cout << "Amerício FWHM\'s\n";
    deltaChnMev(10.96,0);
    deltaChnMev(9.25,0);
    deltaChnMev(9.31,0);
    deltaChnMev(11.15,0);
    std::cout << "RESOLUTIONS\n";
    resol(5.4917,0.0074,1.954*0.01,0.01*0.01);
    resol(5.4480,0.0073,1.649*0.01,0.009*0.01);
    resol(5.3923,0.0071,1.660*0.01,0.009*0.01);
    resol(5.3043,0.0069,1.998*0.01,0.01*0.01);

}
