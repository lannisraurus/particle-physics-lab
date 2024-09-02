#include "data_colector.cpp"

int main(){
    
    data_colector alfa("input/alfa_3_data.txt");
    vector<double> x = alfa.get_a_certain_col(2);
    vector<double> FWHM = alfa.get_a_certain_col(3);
    vector<double> N = alfa.get_a_certain_col(4);
    vector<double> ex;
    vector<double> y = alfa.get_a_certain_col(1);
    vector<double> ey;
    Int_t points_numb = x.size();
    double peak_energy_MeV = 5.3044;
    double chn = 372.45;
    double echn = 11.15 / 2.355 / sqrt(1861);
    double e_peak_p_units_MeV = 5.14235;
    double inc_e_peak_p_units_MeV = sqrt(pow(echn * 1.73064 * 0.001, 2) + pow(2.67061 * 0.00001 * 5.3044, 2) + pow(1.21344 * 0.01, 2));

    for (int i = 0; i < x.size(); i++){
        
        ex.push_back(FWHM[i] / 2.355 / sqrt(N[i]));
    }
    
    for (int i = 0; i < x.size(); i++){
        
        ey.push_back(sqrt(pow(- y[i] * peak_energy_MeV / pow(5.14235, 2) * inc_e_peak_p_units_MeV, 2) + pow(peak_energy_MeV / e_peak_p_units_MeV * 0.01, 2)));
        y[i] = y[i] * peak_energy_MeV / e_peak_p_units_MeV;

    }

    double* x_ptr = &x[0];
    double* ex_ptr = &ex[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_ptr, ey_ptr);
    TF1* f = new TF1("f", "[0] * x + [1]");
    TPaveText* pt = new TPaveText(450, 4.6, 600, 5.25, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Channels");
    g->GetXaxis()->SetLimits(200, 650);
    g->GetXaxis()->SetNdivisions(-209);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Energy (MeV)");
    g->GetYaxis()->SetRangeUser(4.5, 6);
    g->GetYaxis()->SetNdivisions(-506);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.10f %c %.10f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.10f %c %.10f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.10f", f->GetChisquare()));
    pt->Draw();

    C->Update();
    C->SaveAs("output/alfa_fit.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    cout << "Energia do pico em unidades do pulser:" << f->GetParameter(0) * chn + f->GetParameter(1) << " MeV" << endl;

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}
