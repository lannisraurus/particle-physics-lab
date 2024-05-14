#include "data_colector.cpp"

int main(){
    
    data_colector alfa("alfa1_data.txt");
    vector<double> x = alfa.get_a_certain_col(1);
    vector<double> FWHM = alfa.get_a_certain_col(2);
    vector<double> N = alfa.get_a_certain_col(3);
    vector<double> ex;
    vector<double> y;
    vector<double> ey;
    Int_t points_numb = x.size();
    double peak_energy_MeV = 5.3044;
    double chn = 372.45;
    double echn = 11.15 / 2.355 / sqrt(1861);

    for (int i = 0; i < x.size(); i++){
        
        ex.push_back(FWHM[i] / 2.355 / sqrt(N[i]));
    }
    
    for (int i = 0; i < x.size(); i++){
        
        y.push_back(x[i] * peak_energy_MeV / chn);
        ey.push_back(sqrt(pow(- x[i] * peak_energy_MeV / pow(chn, 2)  * echn, 2) + pow(peak_energy_MeV / chn * ex[i], 2)));
    }

    double* x_ptr = &x[0];
    double* ex_ptr = &ex[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_ptr, ey_ptr);
    TF1* f = new TF1("f", "[0] * x + [1]");
    TPaveText* pt = new TPaveText(975, 14.5, 1110, 17, "user");

    /*pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(8);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("");
    g->GetXaxis()->SetLimits(725, 1225);
    g->GetXaxis()->SetNdivisions(-210);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Channels");
    g->GetYaxis()->SetRangeUser(13, 25);
    g->GetYaxis()->SetNdivisions(-20212);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);*/

    g->Draw("AP");
    g->Fit("f");
    /*pt->AddText(Form("y = ax + b (counts/s)"));
    pt->AddText(Form("a = %.3f %c %.3f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.3f %c %.3f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.3f", f->GetChisquare()));
    pt->Draw();*/

    C->Update();
    C->SaveAs("_fit.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}