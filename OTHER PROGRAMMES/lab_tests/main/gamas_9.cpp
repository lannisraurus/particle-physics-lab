// Includes
#include "includes.h"

// Main Function
int main(){

    std::vector<double> E = {32,662,1173,1333,26.8,240.6,360.6,612.4,1461.77,40.83,42.36,92.66,127.81,250.34,350.10,778.52,962.0,1097.93},
                        eE = {0,0,0,0,1.5,1.0,1.8,2.3,0.68,0.14,0.22,0.31,0.12,0.32,0.16,0.97,1.0,0.96},

                        R = {19.33,6.22,5.301,4.644,49.25,5.4,7.3,8.14,4.97,10.34,33.404,23.743,9.123,10.178,8.980,9.261,7.567,7.505},
                        eR = {},

                        FWHM = {6.18,41.17,62.17,61.91,13.2,13.0,26.4,49.9,72.7,4.22,14.15,22.0,11.66,25.48,31.44,72.1,72.8,82.4},
                        eFWHM = {0.16,0.40,0.87,0.73,3.3,2.4,4.0,4.9,1.6,0.35,0.66,1.1,0.24,0.97,0.38,3.5,3.5,2.6};
    
    std::cout << "LIST SIZES " << E.size() << " " << eE.size() << " " << R.size() << " " << FWHM.size() << " " << eFWHM.size() << "\n"; 

    // transform into E^-1/2

    for (auto& i: R) i = i*0.01;
    for (int i = 0; i < R.size(); i++){
        eR.push_back( eFWHM[i]/E[i] + FWHM[i]*eE[i]/(E[i]*E[i]) );
        std::cout << "E = " << E[i] << " +- " << eE[i] << ", " << "R = "<< R[i]*100 << " +- " << eR[i]*100 << "\n";
    }

    

    std::cout << "\n\n\n";
    std::vector<double> nE, neE, nR, neR;
    for(int i = 0; i < E.size(); i++){
        if ( (10 <= i && i <= 17) ){
            nE.push_back(E[i]);
            neE.push_back(eE[i]);
            nR.push_back(R[i]);
            neR.push_back(eR[i]);

            std::cout << "E = " << E[i] << " +- " << eE[i] << ", " << "R = "<< R[i] << " +- " << eR[i] << "\n";
        }
    }



    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(nE.size(), nE.data(), nR.data(), neE.data(), neR.data());


    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlue+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1);
    g->SetMarkerSize(1.75);

    g->GetXaxis()->SetTitle("Energy [keV]");
    g->GetXaxis()->SetLimits(0, 1500);
    g->GetXaxis()->SetNdivisions(-515);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Resolution");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 0.5);
    g->GetYaxis()->SetNdivisions(-510);

    TF1* f = new TF1("f", "[0]/TMath::Sqrt(x) + [1]", -100, 2000);
    f->SetParameters(0.2);
    f->SetLineColor(kRed);
    f->SetLineWidth(2);



    g->Fit("f");

    TPaveText* pt = new TPaveText(800, 0.12, 1400, 0.27, "user");

    pt->SetTextSize(0.04);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("y = A/sqrt(x) + b"));
    pt->AddText(Form("A = %.2f %c %.2f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.4f %c %.4f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->AddText(Form("Number of points = %ld", nE.size() ));


    // f->Draw();
    g->Draw("AP");
    // g_abs->Draw("same");
    // g_amb->Draw("AP");
    // g_eur->Draw("AP");
    pt->Draw("same");
    
    C->Update();
    C->SaveAs("output/resol_energia.png");
    C->Clear();


}
