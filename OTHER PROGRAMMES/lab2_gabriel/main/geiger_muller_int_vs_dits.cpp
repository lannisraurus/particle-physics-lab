#include "data_colector.cpp"

int main(){
    
    data_colector gm("dist_data.txt");
    vector<double> x = gm.get_a_certain_col(1);
    double ex_arr[x.size()] = {0};
    vector<double> y = gm.get_a_certain_col(2);
    vector<double> ey = gm.get_a_certain_col(3);
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        x[i] = x[i] * 100;
    }

    double* x_ptr = &x[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_arr, ey_ptr);
    TF1* f = new TF1("f", "[0] * (1 - x * 0.01 / (x * * 0.0001 x + [1] * [1])^(0.5))");
    TPaveText* pt = new TPaveText(3, 550, 4, 750, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Distance to detector entrance (cm)");
    g->GetXaxis()->SetLimits(1, 5.8);
    g->GetXaxis()->SetNdivisions(-412);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Count rate (counts/s)");
    g->GetYaxis()->SetRangeUser(50, 1000);
    g->GetYaxis()->SetNdivisions(-219);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    pt->AddText(Form("y = a / (r + c)^{2} + b (counts/s)"));
    pt->AddText(Form("a = %.3f %c %.3f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.1f %c %.1f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("c = %.4f %c %.4f", f->GetParameter(2), 0xB1, f->GetParError(2)));
    pt->AddText(Form("#chi^{2} = %.3f", f->GetChisquare()));
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