#include "data_colector.cpp"

int main(){
    
    data_colector gm("plateau.txt");
    vector<double> x = gm.get_a_certain_col(1);
    double ex_arr[x.size()] = {0};
    vector<double> y = gm.get_a_certain_col(2);
    vector<double> ey;
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        x[i] = x[i] * 25;
        ey.push_back(sqrt(y[i]) / 5);
        y[i] = y[i] / 5;
    }

    double* x_ptr = &x[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_arr, ey_ptr);
    TF1* f = new TF1("f", "[0]");
    TPaveText* pt = new TPaveText(975, 16, 1110, 17, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(8);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Voltage (V)");
    g->GetXaxis()->SetLimits(725, 1225);
    g->GetXaxis()->SetNdivisions(-210);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Count rate (counts/s)");
    g->GetYaxis()->SetRangeUser(13, 25);
    g->GetYaxis()->SetNdivisions(-20212);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    //pt->AddText(Form("y = ax + b (counts/s)"));
    pt->AddText(Form("y = %.2f %c %.2f (counts/s)", f->GetParameter(0), 0xB1, f->GetParError(0)));
    //pt->AddText(Form("b = %.2f %c %.2f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->Draw();

    C->Update();
    C->SaveAs("gm_fit.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}